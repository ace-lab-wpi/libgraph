# Include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add executables
# add_executable(graph_types graph_types.cpp)
# target_link_libraries(graph_types graph)

# add_executable(test_heuristic test_heuristic.cpp)
# target_link_libraries(test_heuristic graph)

# add_executable(test_iterator test_iterator.cpp)
# target_link_libraries(test_iterator graph)

# add_executable(test_pt_graph test_pt_graph.cpp)
# target_link_libraries(test_pt_graph graph)

add_executable(test_graph_creation test_graph_creation.cpp)
target_link_libraries(test_graph_creation graph)

add_executable(test_dynamic_pq test_dynamic_pq.cpp)
target_link_libraries(test_dynamic_pq graph)

add_executable(test_id test_id.cpp)
# target_link_libraries(test_id graph)