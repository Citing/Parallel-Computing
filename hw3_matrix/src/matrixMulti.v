module matrixMulti(input clk,
                   input rst,
                   input [7:0] A00,
                   input [7:0] A01,
                   input [7:0] A02,
                   input [7:0] A03,
                   input [7:0] A10,
                   input [7:0] A11,
                   input [7:0] A12,
                   input [7:0] A13,
                   input [7:0] A20,
                   input [7:0] A21,
                   input [7:0] A22,
                   input [7:0] A23,
                   input [7:0] A30,
                   input [7:0] A31,
                   input [7:0] A32,
                   input [7:0] A33,
                   input [7:0] B00,
                   input [7:0] B01,
                   input [7:0] B02,
                   input [7:0] B03,
                   input [7:0] B10,
                   input [7:0] B11,
                   input [7:0] B12,
                   input [7:0] B13,
                   input [7:0] B20,
                   input [7:0] B21,
                   input [7:0] B22,
                   input [7:0] B23,
                   input [7:0] B30,
                   input [7:0] B31,
                   input [7:0] B32,
                   input [7:0] B33,
                   output [7:0] Result00,
                   output [7:0] Result01,
                   output [7:0] Result02,
                   output [7:0] Result03,
                   output [7:0] Result10,
                   output [7:0] Result11,
                   output [7:0] Result12,
                   output [7:0] Result13,
                   output [7:0] Result20,
                   output [7:0] Result21,
                   output [7:0] Result22,
                   output [7:0] Result23,
                   output [7:0] Result30,
                   output [7:0] Result31,
                   output [7:0] Result32,
                   output [7:0] Result33);

    wire [7:0] row00;
    wire [7:0] row01;
    wire [7:0] row02;
    wire [7:0] row10;
    wire [7:0] row11;
    wire [7:0] row12;
    wire [7:0] row20;
    wire [7:0] row21;
    wire [7:0] row22;
    wire [7:0] row30;
    wire [7:0] row31;
    wire [7:0] row32;
    wire [7:0] col00;
    wire [7:0] col01;
    wire [7:0] col02;
    wire [7:0] col03;
    wire [7:0] col10;
    wire [7:0] col11;
    wire [7:0] col12;
    wire [7:0] col13;
    wire [7:0] col20;
    wire [7:0] col21;
    wire [7:0] col22;
    wire [7:0] col23;

    wire [7:0] row0;
    wire [7:0] row1;
    wire [7:0] row2;
    wire [7:0] row3;
    wire [7:0] col0;
    wire [7:0] col1;
    wire [7:0] col2;
    wire [7:0] col3;

    reg [7:0] row0_r;
    reg [7:0] row1_r;
    reg [7:0] row2_r;
    reg [7:0] row3_r;
    reg [7:0] col0_r;
    reg [7:0] col1_r;
    reg [7:0] col2_r;
    reg [7:0] col3_r;

    assign row0 = row0_r;
    assign row1 = row1_r;
    assign row2 = row2_r;
    assign row3 = row3_r;
    assign col0 = col0_r;
    assign col1 = col1_r;
    assign col2 = col2_r;
    assign col3 = col3_r;

    integer step;
    
    always @ (posedge clk)
    begin
        if (rst)
        begin
            step = 0;
            row0_r = 0; row1_r = 0; row2_r = 0; row3_r = 0;
            col0_r = 0; col1_r = 0; col2_r = 0; col3_r = 0;
        end
        else
        begin
            step = step + 1;
            case (step)
                1:
                begin
                    row0_r = A00; row1_r = A10; row2_r = A20; row3_r = A30;
                    col0_r = B00; col1_r = B01; col2_r = B02; col3_r = B03;
                end
                2:
                begin
                    row0_r = A01; row1_r = A11; row2_r = A21; row3_r = A31;
                    col0_r = B10; col1_r = B11; col2_r = B12; col3_r = B13;
                end
                3:
                begin
                    row0_r = A02; row1_r = A12; row2_r = A22; row3_r = A32;
                    col0_r = B20; col1_r = B21; col2_r = B22; col3_r = B23;
                end
                4:
                begin
                    row0_r = A03; row1_r = A13; row2_r = A23; row3_r = A33;
                    col0_r = B30; col1_r = B31; col2_r = B32; col3_r = B33;
                end
                default:
                begin
                    row0_r = 0; row1_r = 0; row2_r = 0; row3_r = 0;
                    col0_r = 0; col1_r = 0; col2_r = 0; col3_r = 0;
                end
            endcase
        end
    end


    Cell cell00(.clk(clk),
                .rst(rst),
                .a_in(row0),
                .b_in(col0),
                .a_out(row00),
                .b_out(col00),
                .result(Result00));
    Cell cell01(.clk(clk),
                .rst(rst),
                .a_in(row00),
                .b_in(col1),
                .a_out(row01),
                .b_out(col01),
                .result(Result01));
    Cell cell02(.clk(clk),
                .rst(rst),
                .a_in(row01),
                .b_in(col2),
                .a_out(row02),
                .b_out(col02),
                .result(Result02));
    Cell cell03(.clk(clk),
                .rst(rst),
                .a_in(row02),
                .b_in(col3),
                .a_out(),
                .b_out(col03),
                .result(Result03));

    Cell cell10(.clk(clk),
                .rst(rst),
                .a_in(row1),
                .b_in(col00),
                .a_out(row10),
                .b_out(col10),
                .result(Result10));
    Cell cell11(.clk(clk),
                .rst(rst),
                .a_in(row10),
                .b_in(col01),
                .a_out(row11),
                .b_out(col11),
                .result(Result11));
    Cell cell12(.clk(clk),
                .rst(rst),
                .a_in(row11),
                .b_in(col02),
                .a_out(row12),
                .b_out(col12),
                .result(Result12));
    Cell cell13(.clk(clk),
                .rst(rst),
                .a_in(row12),
                .b_in(col03),
                .a_out(),
                .b_out(col13),
                .result(Result13));

    Cell cell20(.clk(clk),
                .rst(rst),
                .a_in(row2),
                .b_in(col10),
                .a_out(row20),
                .b_out(col20),
                .result(Result20));
    Cell cell21(.clk(clk),
                .rst(rst),
                .a_in(row20),
                .b_in(col11),
                .a_out(row21),
                .b_out(col21),
                .result(Result21));
    Cell cell22(.clk(clk),
                .rst(rst),
                .a_in(row21),
                .b_in(col12),
                .a_out(row22),
                .b_out(col22),
                .result(Result22));
    Cell cell23(.clk(clk),
                .rst(rst),
                .a_in(row22),
                .b_in(col13),
                .a_out(),
                .b_out(col23),
                .result(Result23));

    Cell cell30(.clk(clk),
                .rst(rst),
                .a_in(row3),
                .b_in(col20),
                .a_out(row30),
                .b_out(),
                .result(Result30));
    Cell cell31(.clk(clk),
                .rst(rst),
                .a_in(row30),
                .b_in(col21),
                .a_out(row31),
                .b_out(),
                .result(Result31));
    Cell cell32(.clk(clk),
                .rst(rst),
                .a_in(row31),
                .b_in(col22),
                .a_out(row32),
                .b_out(),
                .result(Result32));
    Cell cell33(.clk(clk),
                .rst(rst),
                .a_in(row32),
                .b_in(col23),
                .a_out(),
                .b_out(),
                .result(Result33));

endmodule
