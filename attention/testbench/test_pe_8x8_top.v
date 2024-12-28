`include "../pe_8x8_top.v"
module test_top();

    reg clk,en,rst_n;
    reg [511:0]key;
    reg [511:0]value;
    reg [511:0]query;
    reg [15:0] debug;
    
    wire [255:0] final_res;
    wire all_done;
    reg [15:0]mem1[0:31],mem2[0:31],mem3[0:31];

    pe_8x8_top control(
        .clk(clk),
        .en(en),
        .rst_n(rst_n),
        .key(key),
        .value(value),
        .query(query),
        .final_res(final_res),
        .all_done(all_done)
    );

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars;
        $readmemh("Y:\\Documents\\codes\\verilog\\attention_project\\attention\\datas\\activations.txt",mem1);
        $readmemh("Y:\\Documents\\codes\\verilog\\attention_project\\attention\\datas\\weights.txt",mem2);
        $readmemh("Y:\\Documents\\codes\\verilog\\attention_project\\attention\\datas\\values.txt",mem3);
    end

    integer i;

    initial begin
        clk <= 0;
        en <= 0;
        rst_n <= 0;
        debug <= 0;
        for (i = 0; i < 32; i = i + 1) begin
            key[i*16 +: 16] <= mem1[i];
            query[i*16 +: 16] <= mem2[i];
            value[i*16 +: 16] <= mem3[i];
        end
        #10 en <= 1;
        #15 rst_n <= 1;
    end

    always #5 clk = ~clk;

    always @(posedge clk or negedge rst_n) begin
        if(en == 1 && rst_n == 1)
            debug <= debug+1;
        if (all_done == 1 || debug == 8'b1111_1111) begin
            $stop;
        end
    end

endmodule