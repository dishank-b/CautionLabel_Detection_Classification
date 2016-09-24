cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )

add_executable( ../Label_Matching ./Labelling.cpp )
target_link_libraries( ../Label_Matching ${OpenCV_LIBS} )

