`timescale 1ns/1ps
module FindMin(
    input wire [127:0]numbers,
    input wire clk,
    input wire start,    // 开始信号。
    input wire rst_n,
    output reg [15:0]result,
    output reg done // 完成信号。
);

    // 将线网解开。
    reg [15:0]nums[0:7];
    reg [15:0]temp1[0:3];
    reg [15:0]temp2[0:1];
    reg [2:0]counter;

    integer i;
    always @(posedge clk or negedge rst_n) begin
        if(rst_n == 0 || start == 0) begin
            for(i=0;i<8;i=i+1)
                nums[i] <= 16'd0;
            for(i=0;i<4;i=i+1)
                temp1[i] <= 16'd0;
            for(i=0;i<2;i=i+1)
                temp2[i] <= 16'd0;
            result <= 16'd0;
            done <= 1'd0;
            counter <= 3'd0;
        end
        else if(rst_n == 1 && start == 1) begin
            nums[0] <= numbers[15:0];
            nums[1] <= numbers[31:16];
            nums[2] <= numbers[47:32];
            nums[3] <= numbers[63:48];
            nums[4] <= numbers[79:64];
            nums[5] <= numbers[95:80];
            nums[6] <= numbers[111:96];
            nums[7] <= numbers[127:112];

            temp1[0] <= (nums[0] < nums[1]) ? nums[0]:nums[1];
            temp1[1] <= (nums[2] < nums[3]) ? nums[2]:nums[3];
            temp1[2] <= (nums[4] < nums[5]) ? nums[4]:nums[5];
            temp1[3] <= (nums[6] < nums[7]) ? nums[6]:nums[7];

            temp2[0] <= (temp1[0] < temp1[1]) ? temp1[0] : temp1[1];
            temp2[1] <= (temp1[2] < temp1[3]) ? temp1[2] : temp1[3];

            result <= (temp2[0] < temp2[1]) ? temp2[0] : temp2[1];
            counter <= counter + 3'd1;
            if (result > 0 || counter > 3'd4)
                done <= 1;
        end
    end

endmodule