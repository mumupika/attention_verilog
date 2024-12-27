`include "../pe_8x8_cluster.v"
module test_pe_8x8();
    // 定义线网和寄存器。
    reg clk;
    reg en;
    reg rst_n;
    reg [15:0]mem1[0:31];
    reg [15:0]mem2[0:31];

    reg [3:0]counter[0:7];  // The counter for each line.
    reg start[0:7]; // The start signal.
    parameter NUMS = 4; // 决定笑容消融的列和行数。

    reg [127:0] input_activations;
    reg [127:0] input_weights;
    reg [7:0] done;


    wire [127:0] output_actives;
    wire [127:0] output_weights;
    wire [2303:0] results;
    wire [63:0] output_done;

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0,test_pe_8x8);
    end

    initial begin
        $readmemh("Y:\\Documents\\codes\\verilog\\attention_project\\attention\\datas\\activations.txt",mem1);
        $readmemh("Y:\\Documents\\codes\\verilog\\attention_project\\attention\\datas\\weights.txt",mem2);
    end

    pe_8x8_cluster cluster(
        .activations(input_activations),
        .weights(input_weights),
        .clk(clk),
        .en(en),
        .rst_n(rst_n),
        .done(done),
        .output_dones(output_done),
        .o_activations(output_actives),
        .o_weights(output_weights),
        .results(results)
    );

    integer i,fd;

    initial begin
        fd = $fopen("Y:\\Documents\\codes\\verilog\\attention_project\\attention\\datas\\attention_test.txt","w");
        clk <= 0;
        en <= 0;
        rst_n <= 0;
        for (i=0;i<8;i=i+1) begin
            input_activations <= 0;
            input_weights <= 0;
            counter[i] <= 0;
            done <= 0;
        end
        #5 en <= 1;
        #10 rst_n <= 1;
    end


/**
 * 我们需要完成以下的输入格式：
 *                4 3 2 1 ->
 *              4 3 2 1 ->
 *            4 3 2 1 ->
 *          4 3 2 1 ->
 *        4 3 2 1 ->
 *      4 3 2 1 ->
 *    4 3 2 1 ->
 * 来进行输入。同样，读取的是mem寄存器内部的值。我们需要读取
 * 八列数据的具体数值，并且在完成读取后插入done信号。
 * 读取的格式应该为：
 * 1. mem[0],mem[1],mem[2],mem[3],done
 * 2. bubble,mem[4],mem[5],mem[6],mem[7],done
 * 3. bubble,bubble,mem[8],mem[9],mem[10],mem[11],done
 * ...
 */
    always #5 clk = ~clk;

    always @(posedge clk) begin
        if (en == 0 || rst_n == 0) begin
            for(i=0;i<8;i=i+1)
                start[i] <= 0;
                input_activations <= 0;
                input_weights <= 0;
                counter[i] <= 0;
        end
        if (output_done[63] == 1) begin
            $fwrite(fd, "%X", results);
            $fclose(fd);
            $finish;
        end
        else if (en == 1 && rst_n == 1) begin
            // 进行计数和计算部分。直到读取完成所有的权重和激励。NUMS=4.
            if(counter[0] < NUMS) begin
                input_activations[15:0] <= mem1[counter[0]];
                input_weights[15:0] <= mem2[counter[0]];
                counter[0] <= counter[0] + 1;
            end
            else if (counter[0] == NUMS) begin
                input_activations[15:0] <= 0;
                input_weights[15:0] <= 0;
                done[0] <= 1;
                counter[0] <= counter[0] + 1;
            end
            else begin
                input_activations[15:0] <= 0;
                input_weights[15:0] <= 0;
            end

            // 持续片选。这里不能偷懒。否则会导致未定义行为。必须手动片选方式并行冒险。
            if (counter[0] > 0 && counter[1] < NUMS) begin
                input_activations[31:16] <= mem1[counter[1] + 4];
                input_weights[31:16] <= mem2[counter[1] + 4];
                counter[1] <= counter[1] + 1;
            end
            else if(counter[1] == NUMS) begin
                input_activations[31:16] <= 0;
                input_weights[31:16] <= 0;
                counter[1] <= counter[1] + 1;
                done[1] <= 1;
            end
            else begin
                input_activations[31:16] <= 0;
                input_weights[31:16] <= 0;
            end
            //
            if (counter[1] > 0 && counter[2] < NUMS) begin
                input_activations[47:32] <= mem1[counter[2] + 8];
                input_weights[47:32] <= mem2[counter[2] + 8];
                counter[2] <= counter[2] + 1;
            end
            else if(counter[2] == NUMS) begin
                input_activations[47:32] <= 0;
                input_weights[47:32] <= 0;
                counter[2] <= counter[2] + 1;
                done[2] <= 1;
            end
            else begin
                input_activations[47:32] <= 0;
                input_weights[47:32] <= 0;
            end
            //
            if (counter[2] > 0 && counter[3] < NUMS) begin
                input_activations[63:48] <= mem1[counter[3] + 12];
                input_weights[63:48] <= mem2[counter[3] + 12];
                counter[3] <= counter[3] + 1;
            end
            else if(counter[3] == NUMS) begin
                input_activations[63:48] <= 0;
                input_weights[63:48] <= 0;
                counter[3] <= counter[2] + 1;
                done[3] <= 1;
            end
            else begin
                input_activations[63:48] <= 0;
                input_weights[63:48] <= 0;
            end
            //
            if (counter[3] > 0 && counter[4] < NUMS) begin
                input_activations[79:64] <= mem1[counter[4] + 16];
                input_weights[79:64] <= mem2[counter[4] + 16];
                counter[4] <= counter[4] + 1;
            end
            else if(counter[4] == NUMS) begin
                input_activations[79:64] <= 0;
                input_weights[79:64] <= 0;
                counter[4] <= counter[4] + 1;
                done[4] <= 1;
            end
            else begin
                input_activations[79:64] <= 0;
                input_weights[79:64] <= 0;
            end
            //
            if (counter[4] > 0 && counter[5] < NUMS) begin
                input_activations[95:80] <= mem1[counter[5] + 20];
                input_weights[95:80] <= mem2[counter[5] + 20];
                counter[5] <= counter[5] + 1;
            end
            else if(counter[5] == NUMS) begin
                input_activations[95:80] <= 0;
                input_weights[95:80] <= 0;
                counter[5] <= counter[5] + 1;
                done[5] <= 1;
            end
            else begin
                input_activations[95:80] <= 0;
                input_weights[95:80] <= 0;
            end
            //
            if (counter[5] > 0 && counter[6] < NUMS) begin
                input_activations[111:96] <= mem1[counter[6] + 24];
                input_weights[111:96] <= mem2[counter[6] + 24];
                counter[6] <= counter[6] + 1;
            end
            else if(counter[6] == NUMS) begin
                input_activations[111:96] <= 0;
                input_weights[111:96] <= 0;
                counter[6] <= counter[4] + 1;
                done[6] <= 1;
            end
            else begin
                input_activations[111:96] <= 0;
                input_weights[111:96] <= 0;
            end
            //
            if (counter[6] > 0 && counter[7] < NUMS) begin
                input_activations[127:112] <= mem1[counter[7] + 28];
                input_weights[127:112] <= mem2[counter[7] + 28];
                counter[7] <= counter[7] + 1;
            end
            else if(counter[7] == NUMS) begin
                input_activations[127:112] <= 0;
                input_weights[127:112] <= 0;
                counter[7] <= counter[7] + 1;
                done[7] <= 1;
            end
            else begin
                input_activations[127:112] <= 0;
                input_weights[127:112] <= 0;
            end
        end
        
    end
endmodule