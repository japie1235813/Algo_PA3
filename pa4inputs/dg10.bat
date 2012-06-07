read_graph -d pa4inputs/dg10.dot
write_max_flow -s v0 -t v9 -o pa4outputs/dg10_mf.dot
is_flow -i pa4outputs/dg10_mf.dot
exit
dot -Tpng pa4inputs/dg10.dot -o pa4outputs/dg10.png
display pa4outputs/dg10.png &
dot -Tpng pa4outputs/dg6_mf.dot -o pa4outputs/dg6_mf.png
display pa4outputs/dg6_mf.png &