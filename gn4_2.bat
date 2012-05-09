read_graph inputs/gn4.dot 
write_tree_dfs -s v2 -o outputs/gn4_dfs_2.dot
exit
write_tree_bfs -s v0 -o outputs/gn4_bfs.dot
write_tree_mst -a prim -r v0 -o output/gn4_mst_p.dot
is_spanning_tree -i output/gn4_mst_p.dot
