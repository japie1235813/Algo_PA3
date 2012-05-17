
read_graph inputs/gn4.dot
write_tree_mst -a prim -r v0 -o outputs/gn4_mst_p_2.dot
exit
read_graph inputs/gn100.dot
#dot -Tpng inputs/gn10.dot -o outputs/gn10.png
#display outputs/gn10.png
write_tree_bfs -s v0 -o outputs/gn10_bfs_2.dot
write_tree_dfs -s v0 -o outputs/gn10_dfs_2.dot
#dot -Tpng inputs/gn10_dfs.dot -o outputs/gn10_dfs.png
#display outputs/gn10_dfs.png
is_spanning_tree -i outputs/gn4_mst_p_2.dot
