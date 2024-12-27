`include "pe_8x8_cluster.v"
`include "min.v"
module pe_8x8_top(
    input wire clk,
    input wire en,
    input wire rst_n,
    input wire [127:0]key,
    input wire [127:0]value,
    input wire [127:0]query,
    input wire [7:0] done,
    output reg [1023:0] attention_map,
    output reg [255:0] final_res
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

    wire [63:0] cluster_calc_done;
    wire [2303:0] original_sums;
    wire [15:0]minimum_results[0:7];
    wire minimum_done[0:7];
    wire calc_done_signals[0:7][0:7];
    wire [35:0]calc_done_results[0:7][0:7];
    


    pe_8x8_cluster cluster(
        .activations(key_attn),
        .weights(query_val),
        .clk(clk),
        .en(en),
        .rst_n(reset_cluster),
        .done(input_done),
        .output_dones(cluster_calc_done),
        .results(original_sums)
    );

    genvar i,j;
    generate
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

        for (i=0;i<8;i=i+1) begin
            for (j=0;j<8;j=j+1) begin
                // done 分线。
                assign calc_done_signals[i][j] = cluster_calc_done[8*i+j];
                assign calc_done_results[i][j] = original_sums[((8*i + j + 1)*36 - 1): (8*i + j)*36];
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
            for (col = 0; col < 8; col = col + 1) begin
                minimum_col_numbers[col] <= 0;
                minimum_start[col] <= 0;
            end
        end
    end
    

    always @(posedge clk or negedge rst_n) begin
        if (en == 1 && rst_n == 1) begin
            // 读入数据并开始计算。
            reset_cluster <= 1;
            key_attn <= key;
            query_val <= value;

            if(calc_done_signals[7][7] == 1)
                reset_cluster <= 0;
            
            // 处理每个单元的量化操作。
            for(row = 0; row < 8; row = row + 1) begin
                for (col = 0; col < 8; col = col + 1) begin
                    // 计算完成信号出现，进行量化操作。
                    if(calc_done_signals[row][col] == 1 && flags[row][col] == 0) begin
                        if (calc_done_results[row][col][28:12]+1'b1 == 0 || calc_done_results[row][col][11:0] > 0)
                            quantified_ans[row][col] <= 16'b1111_1111_1111_1111;
                        else begin
                            if(calc_done_results[row][col][28]==1)
                                quantified_ans[row][col] <= calc_done_results[row][col][27:12] + 1'b1;
                            else
                                quantified_ans[row][col] <= calc_done_results[row][col][27:12];
                        end
                        flags[row][col] <= flags[row][col] + 1;
                    end
                end
            end

            for (col = 0; col < 8; col = col + 1) begin
                if(flags[7][col] == 1) begin
                    minimum_start[col] <= 1;
                end
                if(minimum_done[col] == 1) begin
                    for(row = 0; row < 8; row = row + 1) begin
                        softmax_res[row][col] <= (quantified_ans[row][col] - minimum_results[col]) * (quantified_ans[row][col] - minimum_results[col]);
                        flags[row][col] <= flags[row][col] + 1;
                        minimum_start[col] <= 0;
                    end
                end
            end

            for(row = 0; row < 8; row = row + 1) begin
                for (col = 0; col < 8; col = col + 1) begin
                    if(flags[row][col] == 2) begin
                        if (softmax_res[row][col][28:12]+1'b1 == 0 || softmax_res[row][col][11:0] > 0)
                            quantified_ans[row][col] <= 16'b1111_1111_1111_1111;
                        else begin
                            if(softmax_res[row][col][28]==1)
                                quantified_ans[row][col] <= softmax_res[row][col][27:12] + 1'b1;
                            else
                                quantified_ans[row][col] <= softmax_res[row][col][27:12];
                        end
                        flags[row][col] <= flags[row][col] + 1;
                    end
                end
            end

        end
    end
endmodule