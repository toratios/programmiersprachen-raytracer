add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)

add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

# Build tests
add_executable(tests
  tests.cpp)
target_link_libraries(tests
  ${GLFW_LIBRARIES}
  )



#Build raytracer_test
add_executable(raytracer_test raytracer_test.cpp)

target_link_libraries(raytracer_test ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer_test glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer_test DESTINATION .)


#Build raytracer_sdfloader
add_executable(raytracer_sdfloader raytracer_sdfloader.cpp)

target_link_libraries(raytracer_sdfloader ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer_sdfloader glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer_sdfloader DESTINATION .)

#Build raytracer_transtest
add_executable(raytracer_transtest raytracer_transtest.cpp)

target_link_libraries(raytracer_transtest ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer_transtest glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer_transtest DESTINATION .)
