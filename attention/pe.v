module pe(
    // 输入长度为fix_8_8的无符号整型：
    input wire [15:0] active_left,
    input wire [15:0] in_weight,
    input wire input_done,
    // 时钟,使能,复位信号。
    input wire clk,
    input wire en,
    input wire rst_n,
    // 输出结果。
    output reg [15:0] active_right,
    output reg [35:0] sum,
    output reg [15:0] out_weight,
    output reg calc_done
);

    // 正时钟沿进行触发，负复位沿进行复位。
    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'd0 || en == 1'd0) begin
            sum <= 0;
            active_right <= 0;
            out_weight <= 0;
            calc_done <= 0;
        end
        else if(rst_n == 1'd1 && en == 1'd1) begin
            sum <= in_weight * active_left + sum;
            out_weight <= in_weight;
            active_right <= active_left;
            calc_done <= input_done;
        end
    end
endmodule