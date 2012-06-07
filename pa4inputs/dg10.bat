read_graph -d pa4inputs/dg10.dot
write_max_flow -s v0 -t v9 -o pa4outputs/dg10_mf.dot
dot -Tpng pa4inputs/dg10.dot -o pa4outputs/dg10.png
display pa4outputs/dg10.png &
exit
dot -Tpng outputs/dg6_mf.dot -o outputs/dg6_mf.png
display outputs/dg6_mf.png &
is_flow -i outputs/dg6_mf.dot