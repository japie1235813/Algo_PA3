read_graph -d pa4inputs/dg6.dot
exit
dot -Tpng pa4inputs/dg6.dot -o pa4outputs/dg6.png
display pa4outputs/dg6.png &
write_max_flow -s v0 -t v5 -o pa4outputs/dg6_mf.dot
dot -Tpng pa4outputs/dg6_mf.dot -o pa4outputs/dg6_mf.png
display pa4outputs/dg6_mf.png &
is_flow -i pa4outputs/dg6_mf.dot