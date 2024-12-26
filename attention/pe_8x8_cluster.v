/**
 * 8x8模块接线和集群。
*/
`include "pe.v"
module pe_8x8_cluster(
    input wire [127:0] activations,
    input wire [127:0] weights,
    input wire clk,
    input wire en,
    input wire rst_n,
    input wire [7:0] done,    // 用于判断计算结束。
    output reg [7:0] output_dones,
    output reg [127:0] o_activations,
    output reg [127:0] o_weights,
    output wire [2303:0] results
);
    // 定义内部线网。
    wire [15:0]pe_output_weights[0:8][0:7];
    wire [15:0]pe_output_activates[0:7][0:8];
    wire done_signals[0:7][0:7];
    wire [35:0]pe_output_sums[0:7][0:7];

    // 定义内部寄存器。
    reg [35:0]store_orig_sums[0:7][0:7];
    reg [15:0]store_output_sums[0:7][0:7];

    genvar i,j;
    // 输入线网链接。
    generate
        for(i = 0; i < 8; i = i + 1) begin
                assign pe_output_activates[i][0] = activations[((i+1)*16-1):i*16];
                assign pe_output_weights[0][i] = weights[((i+1)*16-1):i*16];
        end
    endgenerate

    // 输出线网连接。
    assign results = 
    {  
        store_orig_sums[7][7],
        store_orig_sums[7][6],
        store_orig_sums[7][5],
        store_orig_sums[7][4],
        store_orig_sums[7][3],
        store_orig_sums[7][2],
        store_orig_sums[7][1],
        store_orig_sums[7][0],
        store_orig_sums[6][7],
        store_orig_sums[6][6],
        store_orig_sums[6][5],
        store_orig_sums[6][4],
        store_orig_sums[6][3],
        store_orig_sums[6][2],
        store_orig_sums[6][1],
        store_orig_sums[6][0],
        store_orig_sums[5][7],
        store_orig_sums[5][6],
        store_orig_sums[5][5],
        store_orig_sums[5][4],
        store_orig_sums[5][3],
        store_orig_sums[5][2],
        store_orig_sums[5][1],
        store_orig_sums[5][0],
        store_orig_sums[4][7],
        store_orig_sums[4][6],
        store_orig_sums[4][5],
        store_orig_sums[4][4],
        store_orig_sums[4][3],
        store_orig_sums[4][2],
        store_orig_sums[4][1],
        store_orig_sums[4][0],
        store_orig_sums[3][7],
        store_orig_sums[3][6],
        store_orig_sums[3][5],
        store_orig_sums[3][4],
        store_orig_sums[3][3],
        store_orig_sums[3][2],
        store_orig_sums[3][1],
        store_orig_sums[3][0],
        store_orig_sums[2][7],
        store_orig_sums[2][6],
        store_orig_sums[2][5],
        store_orig_sums[2][4],
        store_orig_sums[2][3],
        store_orig_sums[2][2],
        store_orig_sums[2][1],
        store_orig_sums[2][0],
        store_orig_sums[1][7],
        store_orig_sums[1][6],
        store_orig_sums[1][5],
        store_orig_sums[1][4],
        store_orig_sums[1][3],
        store_orig_sums[1][2],
        store_orig_sums[1][1],
        store_orig_sums[1][0],
        store_orig_sums[0][7],
        store_orig_sums[0][6],
        store_orig_sums[0][5],
        store_orig_sums[0][4],
        store_orig_sums[0][3],
        store_orig_sums[0][2],
        store_orig_sums[0][1],
        store_orig_sums[0][0]
    };
    
    // 模块实例化。
    pe pe_00(
        .active_left(pe_output_activates[0][0]),
        .in_weight(pe_output_weights[0][0]),
        .input_done(done[0]),
        .clk(clk),
        .en(en),
        .rst_n(rst_n),
        .active_right(pe_output_activates[0][1]),
        .out_weight(pe_output_weights[1][0]),
        .sum(pe_output_sums[0][0]),
        .calc_done(done_signals[0][0])
    );

    // weight 顶层实例化。
    generate
        for(i=1;i<8;i=i+1) begin
            pe pe_0i(
                .active_left(pe_output_activates[0][i]),
                .in_weight(pe_output_weights[0][i]),
                .input_done(done_signals[0][i-1]),
                .clk(clk),
                .en(en),
                .rst_n(rst_n),
                .active_right(pe_output_activates[0][i+1]),
                .out_weight(pe_output_weights[1][i]),
                .sum(pe_output_sums[0][i]),
                .calc_done(done_signals[0][i])
            );
        end
    endgenerate
    // activations 顶层实例化。
    generate
        for(i=1;i<8;i=i+1)begin
            pe pe_i0(
                .active_left(pe_output_activates[i][0]),
                .in_weight(pe_output_weights[i][0]),
                .input_done(done[i]),
                .clk(clk),
                .en(en),
                .rst_n(rst_n),
                .active_right(pe_output_activates[i][1]),
                .out_weight(pe_output_weights[i+1][0]),
                .sum(pe_output_sums[i][0]),
                .calc_done(done_signals[i][0])
            );
        end
    endgenerate

    // 通用pe单元初始化。
    generate
        for(i=1;i<8;i=i+1) begin
            for(j=1;j<8;j=j+1) begin
                pe pe_general(
                    .active_left(pe_output_activates[i][j]),
                    .in_weight(pe_output_weights[i][j]),
                    .input_done(done_signals[i][j-1]),
                    .clk(clk),
                    .en(en),
                    .rst_n(rst_n),
                    .active_right(pe_output_activates[i][j+1]),
                    .out_weight(pe_output_weights[i+1][j]),
                    .sum(pe_output_sums[i][j]),
                    .calc_done(done_signals[i][j])
                );
            end
        end
    endgenerate
    // 相关寄存器控制。
    integer row,col;
    always @(posedge clk or negedge rst_n) begin
        if (en == 0 || rst_n == 0) begin
            for (row = 0; row < 8; row = row + 1) begin
                for(col = 0; col < 8; col = col + 1) begin
                    store_orig_sums[row][col] <= 36'b0;
                    store_output_sums[row][col] <= 16'b0;
                end
            end
            for (row = 0; row < 8; row = row + 1) begin
                output_dones [row] <= 0;
            end
        end
        else if (en == 1 || rst_n == 1) begin
            for(row = 0; row < 8; row = row + 1) begin
                for (col = 0; col < 8; col = col + 1) begin
                    store_orig_sums[row][col] <= pe_output_sums[row][col];
                end
            end
            for (row = 0; row < 8; row = row + 1) begin
                output_dones [row] <= done_signals[row][7];
            end
        end
    end
endmodule