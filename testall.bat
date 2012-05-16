read_graph inputs/gn4.dot
write_tree_dfs -s v0 -o outputs/gn4_dfs_2.dot
write_tree_bfs -s v0 -o outputs/gn4_bfs_2.dot
write_tree_mst -a prim -r v0 -o outputs/gn4_mst_p_2.dot
is_spanning_tree -i outputs/gn4_mst_p_2.dot

read_graph inputs/gn10.dot
write_tree_dfs -s v0 -o outputs/gn10_dfs_2.dot
write_tree_bfs -s v0 -o outputs/gn10_bfs_2.dot
write_tree_mst -a prim -r v0 -o outputs/gn10_mst_p_2.dot
is_spanning_tree -i outputs/gn10_mst_p_2.dot

read_graph inputs/gn100.dot
write_tree_dfs -s v0 -o outputs/gn100_dfs_2.dot
write_tree_bfs -s v0 -o outputs/gn100_bfs_2.dot
write_tree_mst -a prim -r v0 -o outputs/gn100_mst_p_2.dot
is_spanning_tree -i outputs/gn100_mst_p_2.dot

read_graph inputs/gn1000.dot
write_tree_dfs -s v0 -o outputs/gn1000_dfs_2.dot
write_tree_bfs -s v0 -o outputs/gn1000_bfs_2.dot
write_tree_mst -a prim -r v0 -o outputs/gn1000_mst_p_2.dot
is_spanning_tree -i outputs/gn1000_mst_p_2.dot

read_graph inputs/gn10000.dot
write_tree_dfs -s v0 -o outputs/gn10000_dfs_2.dot
write_tree_bfs -s v0 -o outputs/gn10000_bfs_2.dot
write_tree_mst -a prim -r v0 -o outputs/gn10000_mst_p_2.dot
is_spanning_tree -i outputs/gn10000_mst_p_2.dot

read_graph inputs/gn50000.dot
write_tree_dfs -s v0 -o outputs/gn50000_dfs_2.dot
write_tree_bfs -s v0 -o outputs/gn50000_bfs_2.dot
write_tree_mst -a prim -r v0 -o outputs/gn50000_mst_p_2.dot
is_spanning_tree -i outputs/gn50000_mst_p_2.dot