set(TARGET lockscr)
add_executable(${TARGET} lockscr.cpp drawutils.cpp passHandler.cpp sysutils.cpp)

target_link_libraries(${TARGET} 
                      -l${CAIRO_LIBRARIES} 
                      -lxcb
                      -lxcb-ewmh
                      -lxcb-render
                      -lpthread)
