// `include "pe_8x8_cluster.v"
// `include "min.v"
module pe_8x8_top(
    input wire clk,
    input wire en,
    input wire rst_n,
    input wire [511:0]key,
    input wire [511:0]value,
    input wire [511:0]query,
    output reg [511:0] final_res,
    output reg all_done
);


    reg [127:0] key_attn;   // 进行复用。
    reg [127:0] query_val;  // 进行复用。
    reg [7:0] input_done;
    reg reset_cluster;
    reg [127:0]minimum_col_numbers[0:7];
    reg minimum_start[0:7];
    reg [15:0]quantified_ans[0:7][0:7];
    reg [4:0]flags[0:7][0:7];    // 复用。表示每个阶段每个寄存器状态。
    reg [35:0]softmax_res[0:7][0:7];
    reg [3:0]input_counter[0:7];    // 八路输入控制。
    reg attention_flag;

    wire [63:0] cluster_calc_done;
    wire [2303:0] original_sums;
    wire [15:0]minimum_results[0:7];
    wire minimum_done[0:7];
    wire calc_done_signals[0:7][0:7];
    wire [35:0]calc_done_results[0:7][0:7];
    wire [15:0]input_keys[0:7][0:3];
    wire [15:0]input_values[0:3][0:7];
    wire [15:0]input_queries[0:7][0:3];
    


    pe_8x8_cluster cluster(
        .activations(key_attn),
        .weights(query_val),
        .clk(clk),
        .en(en),
        .rst_n(reset_cluster),
        .done(input_done),
        .o_activations(),
        .o_weights(),
        .output_dones(cluster_calc_done),
        .results(original_sums)
    );

    genvar i,j;
    // 进行线网操作与实例化生成。
    generate
        // 生成最小值模块。
        for (i = 0; i < 8; i = i + 1) begin
            FindMin min(
                .numbers(minimum_col_numbers[i]),
                .clk(clk),
                .start(minimum_start[i]),
                .rst_n(rst_n),
                .result(minimum_results[i]),
                .done(minimum_done[i])
            );
        end
        // 生成计算信号和计算结果。
        for (i=0;i<8;i=i+1) begin
            for (j=0;j<8;j=j+1) begin
                assign calc_done_signals[i][j] = cluster_calc_done[8*i+j];
                assign calc_done_results[i][j] = original_sums[((8*i + j + 1)*36 - 1): (8*i + j)*36];
            end
        end

        // 将输入数据处理成需要的线网。
        for (i=0;i<8;i=i+1) begin
            for (j=0;j<4;j=j+1) begin
                assign input_keys[i][j] = key[(4*i+j+1) * 16 - 1 : (4*i+j)*16];
                assign input_queries[i][j] = query[(4*i+j+1)*16-1 : (4*i+j)*16];
            end
        end

        for(i=0;i<4;i=i+1) begin
            for(j=0;j<8;j=j+1) begin
                 assign input_values[i][j] = value[(8*i+j+1)*16-1:(8*i+j)*16];
            end
        end
    endgenerate

    integer row,col;
    always @(posedge clk or negedge rst_n) begin
        if(en == 0 || rst_n == 0) begin
            key_attn <= 0;
            query_val <= 0;
            input_done <= 0;
            reset_cluster <= 0;
            all_done <= 0;
            attention_flag <= 0;
            final_res <= 0;
            for (col = 0; col < 8; col = col + 1) begin
                minimum_col_numbers[col] <= 0;
                minimum_start[col] <= 0;
                input_counter[col] <= 0;
            end

            for (row = 0; row < 8; row = row + 1) begin
                for(col = 0; col < 8; col = col + 1) begin
                    quantified_ans[row][col] <= 0;
                    flags[row][col] <= 0;
                    softmax_res[row][col] <= 0;
                end
            end
        end
    end
    

    always @(posedge clk or negedge rst_n) begin
        if (en == 1 && rst_n == 1) begin
            // 读入数据并开始计算。
            reset_cluster <= 1;
            
            // 处理数据读入操作。flag此时为0.
            if(attention_flag == 0)  begin
                if(input_counter[0] >= 0 && input_counter[0] <= 4)
                    input_counter[0] <= input_counter[0] + 1;
                for(row = 0; row < 8; row = row + 1) begin
                    if(input_counter[row] > 0 && input_counter[row] <= 4) begin
                        key_attn[row*16 +: 16] <= input_keys[row][input_counter[row] - 1];
                        query_val[row*16 +: 16] <= input_queries[row][input_counter[row] - 1];
                        input_counter[row] <= input_counter[row] + 1;
                        if(row + 1 < 8)
                            input_counter[row+1] <= input_counter[row+1] + 1;
                    end
                    else if(input_counter[row] > 4) begin
                        input_done[row] <= 1;
                        key_attn[row*16 +: 16] <= 0;
                        query_val[row*16 +: 16] <= 0;
                    end
                end
            end
            
    

            // 处理每个单元的量化操作。flag处理完成为1.
            for(row = 0; row < 8; row = row + 1) begin
                for (col = 0; col < 8; col = col + 1) begin
                    // 计算完成信号出现，进行量化操作。
                    if(calc_done_signals[row][col] == 1 && flags[row][col] == 0) begin
                        if (calc_done_results[row][col][23:7]+1'b1 == 0 || calc_done_results[row][col][35:24] > 0)
                            quantified_ans[row][col] <= 16'b1111_1111_1111_1111;
                        else begin
                            if(calc_done_results[row][col][7]==1)
                                quantified_ans[row][col] <= calc_done_results[row][col][23:8] + 1'b1;
                            else
                                quantified_ans[row][col] <= calc_done_results[row][col][23:8];
                        end
                        flags[row][col] <= flags[row][col] + 1;
                    end
                end
            end

            // 归零所有pe单元。输入数据。
            if(flags[7][7] >= 1 && flags[7][7] < 3) begin
                reset_cluster <= 0;
                attention_flag <= 1;
                key_attn <= 0;
                query_val <= 0;
                input_done <= 0;
                for (col = 0; col < 8; col = col + 1) 
                    input_counter[col] <= 0;
            end
                
            // 对每一列所有元素进行softmax操作。flag处理完成为2.
            for (col = 0; col < 8; col = col + 1) begin
                if(flags[7][col] == 1) begin
                    minimum_start[col] <= 1;
                    for (row = 0; row < 8; row = row + 1) begin
                        minimum_col_numbers[col][row * 16 +: 16] <= quantified_ans[row][col];
                    end
                end
                if(minimum_done[col] == 1) begin
                    for(row = 0; row < 8; row = row + 1) begin
                        softmax_res[row][col] <= (quantified_ans[row][col] - minimum_results[col]) * (quantified_ans[row][col] - minimum_results[col]);
                        flags[row][col] <= flags[row][col] + 1;
                        minimum_start[col] <= 0;
                    end
                end
            end

            // 再次进行量化操作。flag处理完成为3.
            for(row = 0; row < 8; row = row + 1) begin
                for (col = 0; col < 8; col = col + 1) begin
                    if(flags[row][col] == 2) begin
                        if (softmax_res[row][col][23:7]+1'b1 == 0 || softmax_res[row][col][35:24] > 0)
                            quantified_ans[row][col] <= 16'b1111_1111_1111_1111;
                        else begin
                            if(softmax_res[row][col][7]==1)
                                quantified_ans[row][col] <= softmax_res[row][col][23:8] + 1'b1;
                            else
                                quantified_ans[row][col] <= softmax_res[row][col][23:8];
                        end
                        flags[row][col] <= flags[row][col] + 1;
                    end
                end
            end

            // 读入新的数据。
            if (flags[7][7] == 3 && attention_flag <= 1) begin
                if(input_counter[0] >= 0 && input_counter[0] <= 8)
                    input_counter[0] <= input_counter[0] + 1;
                for(row = 0; row < 8; row = row + 1) begin
                    if (input_counter[row]>0 && input_counter[row]<=8) begin
                        key_attn[row*16 +: 16] <= quantified_ans[input_counter[row] - 1][row];
                        if(row < 4)
                            query_val[row*16 +: 16] <= input_values[row][input_counter[row] - 1];
                        else
                            query_val[row*16 +: 16] <= 0;
                        input_counter[row] <= input_counter[row] + 1;
                        if(row+1<8)
                            input_counter[row+1] <= input_counter[row+1] + 1;
                    end
                    else if (input_counter[row] > 8) begin
                        input_done[row] <= 1;
                        key_attn[row*16 +: 16] <= 0;
                        query_val[row*16 +: 16] <= 0;
                    end
                end
            end

            // 处理每个单元的量化操作。flag处理完成为4.
            for(row = 0; row < 8; row = row + 1) begin
                for (col = 0; col < 4; col = col + 1) begin
                    // 计算完成信号出现，进行量化操作。
                    if(calc_done_signals[row][col] == 1 && flags[row][col] == 3) begin
                        if (calc_done_results[row][col][23:7]+1'b1 == 0 || calc_done_results[row][col][35:24] > 0)
                            quantified_ans[row][col] <= 16'b1111_1111_1111_1111;
                        else begin
                            if(calc_done_results[row][col][7]==1)
                                quantified_ans[row][col] <= calc_done_results[row][col][23:8] + 1'b1;
                            else
                                quantified_ans[row][col] <= calc_done_results[row][col][23:8];
                        end
                        flags[row][col] <= flags[row][col] + 1;
                    end
                end
            end
            if(flags[7][3] == 4) begin
                for(row = 0; row < 8; row = row + 1) begin
                    for(col = 0; col < 4; col = col + 1) begin
                        final_res[(4*row + col)*16 +: 16] <= quantified_ans[row][col];
                        flags[row][col] <= flags[row][col] + 1;
                    end
                end
            end

            if(flags[7][3] == 5)
                all_done <= 1;
        end
    end
endmodule