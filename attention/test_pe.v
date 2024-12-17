module test_pe();
    // 输入模块
    reg clk;
    reg en;
    reg rst_n;
    // 输入激励
    reg [15:0] activations;
    reg [15:0] weights;
    // 输出结果
    wire [15:0] output_a;
    wire [15:0] output_w;
    wire [35:0] output_sum;

    // SRAM:
    reg [15:0] mem1[0:3];
    reg [15:0] mem2[0:3];

    // 计数器
    reg [2:0] counter;

    // 接线：
    pe pe_module(
        .active_left(activations),
        .in_weight(weights),
        .clk(clk),
        .en(en),
        .rst_n(rst_n),
        .active_right(output_a),
        .out_weight(output_w),
        .sum(output_sum)
    );


    initial begin
        $readmemh("activations.txt", mem1);
        $readmemh("weights.txt", mem2);
        clk = 0;
        en = 0;
        rst_n = 0;
        #10 en = 1;
        #15 rst_n = 1;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, test_pe);
    end

    always #5 clk = ~clk;   // 五秒钟反转一次。
    always @ (posedge clk or negedge rst_n) begin
        if (rst_n == 1 && en == 1) begin
            if (counter == 3'b111) begin
                $finish;
            end
            if (counter <= 3'b011) begin
                activations <= mem1[counter];
                weights <= mem2[counter];
                counter <= counter + 1'b1;
            end
            else begin
                activations <= 16'b0;
                weights <= 16'b0;
                counter <= counter + 1'b1;
            end
        end
        else begin
            activations <= 16'b0;
            weights <= 16'b0;
            counter <= 3'b0;
        end
    end

endmodule