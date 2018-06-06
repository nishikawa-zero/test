module axi_slave (
    clk
  , s1_araddr
  , s1_arready
  , s1_arvalid
  , s1_awaddr
  , s1_awready
  , s1_rready
  , s1_rvalid
  , s1_rdata
  , s1_rlast
  , s1_wready
  , s1_wvalid
  , s1_wdata
  , s1_wstrb
  , trigger
  , rlast_ctrl
);
parameter A_MAX=256;
input  clk;
input  [31:0] s1_araddr;
input  [31:0] s1_awaddr;
input  s1_arvalid;
input  s1_rready;
output s1_rvalid;
output [127:0] s1_rdata;
output s1_rlast;
output s1_wready;
input  s1_wvalid;
input  [127:0] s1_wdata;
input  [3:0] s1_wstrb;
input  trigger;
input  [31:0] rlast_ctrl;
output s1_arready;
output s1_awready;

reg s1_rvalid; initial s1_rvalid = 1'b0;
reg s1_wready; initial s1_wready = 1'b1;
reg s1_rlast;
initial begin
  if (rlast_ctrl == 1) s1_rlast = 1'b1;
  else                 s1_rlast = 1'b0;
end
reg s1_arready;initial s1_arready = 1'b1;
reg s1_awready;initial s1_awready = 1'b1;

reg [31:0] r_addr;
reg [31:0] w_addr;
reg [4:0]  rdata_cnt;

reg [127:0] mem [0:A_MAX-1];

integer ii;
initial begin
  for (ii=0; ii<A_MAX; ii=ii+1) mem[ii] = ii;
end

always @(posedge clk) begin
  if (s1_rvalid && s1_rready) begin
    r_addr <= r_addr + 1;

    if (rdata_cnt == rlast_ctrl - 1)
      rdata_cnt <= 0;
    else
      rdata_cnt <= (rdata_cnt + 1);

    if (rdata_cnt == rlast_ctrl - 2)
      s1_rlast <= 1;
    else
      s1_rlast <= 0;
  end
end

always @(posedge clk) begin
  if (s1_rvalid == 0) begin
    if (s1_arvalid && s1_arready) s1_rvalid <= 1;
  end
end

always @(posedge clk) begin
  if (s1_wvalid && s1_wready) w_addr <= w_addr + 1;
end

always @(posedge clk) begin
  s1_wready <= trigger;
end

assign s1_rdata = mem[r_addr];

endmodule

