`include "../min.v"
module test_min ();

    // SRAM
    reg [15:0] mem[0:7];
    reg [127:0] prepare_input;
    reg clk,start,rst_n;

    wire [15:0] res;
    reg [3:0] counter;
    wire done;

    FindMin min(
        .numbers(prepare_input),
        .clk(clk),
        .start(start),
        .rst_n(rst_n),
        .done(done),
        .result(res)
    );

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, test_min);
        prepare_input <= 0;
        clk <= 0;
        start <= 0;
        rst_n <= 0;
        counter <= 0;
        $readmemh("Y:\\Documents\\codes\\verilog\\attention_project\\attention\\datas\\minimum.txt",mem);
        #5 start <= 1;
        #5 rst_n <= 1;
    end

    always #5 clk = ~clk;

    always @(posedge clk or negedge rst_n) begin
        if(rst_n == 0 || start == 0) begin
            prepare_input <= 0;
            counter <= 0;
        end
        if(done == 1) begin
            start <= 0;
            rst_n <= 0;
            #5 $finish;
        end
        else begin
            prepare_input[15:0] <= mem[0];
            prepare_input[31:16] <= mem[1];
            prepare_input[47:32] <= mem[2];
            prepare_input[63:48] <= mem[3];
            prepare_input[79:64] <= mem[4];
            prepare_input[95:80] <= mem[5];
            prepare_input[111:96] <= mem[6];
            prepare_input[127:112] <= mem[7];
            counter <= counter + 1;
        end
    end

    
endmodule