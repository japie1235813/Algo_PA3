
read_graph inputs/gn1000.dot
write_tree_mst -a prim -r v0 -o tmp1000
exit
write_tree_bfs -s v0 -o outputs/gn1000_bfs_2.dot
write_tree_dfs -s v0 -o outputs/gn1000_dfs_2.dot
read_graph inputs/gn100.dot
#dot -Tpng inputs/gn10.dot -o outputs/gn10.png
#display outputs/gn10.png
#dot -Tpng inputs/gn10_dfs.dot -o outputs/gn10_dfs.png
#display outputs/gn10_dfs.png
is_spanning_tree -i outputs/gn4_mst_p_2.dot
