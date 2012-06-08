read_graph -d pa4inputs/dg10.dot
write_max_flow -s v0 -t v9 -o pa4outputs/dg10_mf.dot
is_flow -i pa4outputs/dg10_mf.dot
read_graph -d pa4inputs/dg100.dot
write_max_flow -s v0 -t v99 -o pa4outputs/dg100_mf.dot
is_flow -i pa4outputs/dg100_mf.dot
read_graph -d pa4inputs/dg1000.dot
write_max_flow -s v0 -t v999 -o pa4outputs/dg1000_mf.dot
is_flow -i pa4outputs/dg100_mf.dot
read_graph -d pa4inputs/dg5000.dot
write_max_flow -s v0 -t v4999 -o pa4outputs/dg5000_mf.dot
is_flow -i pa4outputs/dg100_mf.dot
exit
