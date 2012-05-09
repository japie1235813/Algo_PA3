read_graph inputs/gn10.dot 
write_tree_dfs -o outputs/gn10_dfs_2.dot -s v0 
exit
write_tree_bfs -s v0 -o outputs/gn4_bfs.dot
write_tree_mst -a prim -r v0 -o output/gn4_mst_p.dot
is_spanning_tree -i output/gn4_mst_p.dot
