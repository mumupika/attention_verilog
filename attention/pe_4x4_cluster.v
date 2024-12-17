`include "pe.v"
module pe_4x4_cluster(
    input wire [63:0] activations,
    input wire [63:0] weights,
    input wire clk,
    input wire en,
    input wire rst_n,
    output reg [63:0] o_activations,
    output reg [63:0] o_weights,
    output reg [63:0] results
);

    // 定义内部线网。
    wire [15:0] output_actives[0:3][0:3];
    wire [15:0] output_weights[0:3][0:3];
    wire [35:0] output_results[0:3][0:3];

    // 寄存器用于暂存。
    reg [15:0] out_actives[0:3][0:3];
    reg [15:0] out_weights[0:3][0:3];
    reg [35:0] out_results[0:3][0:3];

    // 实例化特殊的pe11.
    pe pe11(
        .active_left(activations[15:0]),
        .in_weight(weights[15:0]),
        .clk(clk),
        .en(en),
        .rst_n(rst_n),
        .active_right(output_actives[0][0]),
        .sum(output_results[0][0]),
        .out_weight(output_weights[0][0])
    );
    // 生成块进行实例化。
    genvar i,j;
    /********************/
    generate
        for(i = 1; i < 4; i = i + 1) begin:col_top
            pe pe_col_top(
                .active_left(activations[((i+1)*16-1):(i*16)]),
                .in_weight(output_weights[i-1][0]),
                .clk(clk),
                .en(en),
                .rst_n(rst_n),
                .active_right(output_actives[i][0]),
                .sum(output_results[i][0]),
                .out_weight(output_weights[i][0])
            );
        end
    endgenerate
    /********************/
    generate
        for (i = 1; i < 4; i = i + 1) begin:row_top
            pe pe_row_top(
                .active_left(output_actives[0][i-1]),
                .in_weight(weights[((i+1)*16-1):(i*16)]),
                .clk(clk),
                .en(en),
                .rst_n(rst_n),
                .active_right(output_actives[0][i]),
                .sum(output_results[0][i]),
                .out_weight(output_weights[0][i])
            );
        end
    endgenerate

    generate
        for (i = 1; i < 3; i = i + 1) begin
            for (j = 1; j < 3; j = j + 1) begin
                pe typical_pe(
                    .active_left(output_actives[i][j-1]),
                    .in_weight(output_weights[i-1][j]),
                    .clk(clk),
                    .en(en),
                    .rst_n(rst_n),
                    .active_right(output_actives[i][j]),
                    .sum(output_results[i][j]),
                    .out_weight(output_weights[i][j])
                );
            end
        end
    endgenerate
    /********************/
    generate
        // TODO
    endgenerate
    /********************/
    always @ (posedge clk or negedge rst_n) begin
        // 初始化，将所有寄存器设置为0.
        if(rst_n == 1'd0 || en == 1'd0) begin:initialize
            integer i,j;
            for (i = 0; i < 4; i = i + 1) begin
                for (j = 0; j < 4; j = j + 1) begin
                    out_actives[i][j] <= 16'd0;
                    out_weights[i][j] <= 16'd0;
                    out_results[i][j] <= 35'd0;
                end
            end
        end

        else if(rst_n == 1'd1 && en == 1'd1) begin: calculation
            
        end
    end
endmodule