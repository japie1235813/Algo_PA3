read_graph inputs/gn4.dot 
#dot Tpng inputs/gn4.dot -o outputs/gn4.png
#display outputs/gn4.png
write_tree_dfs -s v0 -o outputs/gn4_dfs_2.dot
#dot -Tpng inputs/gn4_dfs.dot -o outputs/gn4_dfs.png
#display outputs/gn4_dfs.png
write_tree_bfs -s v0 -o outputs/gn4_bfs_2.dot
write_tree_mst -a prim -r v0 -o output/gn4_mst_p.dot
exit
is_spanning_tree -i output/gn4_mst_p.dot
