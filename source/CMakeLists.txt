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


#Build raytracer_animation
add_executable(raytracer_animation raytracer_animation.cpp)

target_link_libraries(raytracer_animation ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer_animation glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer_animation DESTINATION .)

#Build sdf_generator
add_executable(sdf_generator sdf_generator.cpp)

target_link_libraries(sdf_generator ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(sdf_generator glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS sdf_generator DESTINATION .)

