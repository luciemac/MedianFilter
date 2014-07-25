# Test on the output for a given threshold
set(Data Data) 

set(TEMP_DIR ${MedianFilter_BINARY_DIR}/Testing/Temporary )
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${Data} )

set(Reference1 ${SOURCE_DIR}/output_rad-2.nrrd )
set(Reference2 ${SOURCE_DIR}/output_rad-4.nrrd )
set(FakeOutput ${SOURCE_DIR}/FakeOutput.nrrd )

set(Input ${SOURCE_DIR}/inputT2.nrrd )

include_directories( ${CMAKE_SOURCE_DIR} )
add_executable(MedianFilterTest MedianFilterTest.cxx)
target_link_libraries(MedianFilterTest MedianFilterLib)
set( RadiusValue2 ${TEMP_DIR}/RadiusValue2.nrrd )
set( RadiusValue4 ${TEMP_DIR}/RadiusValue4.nrrd )


# Test checking that the program cannot run without arguments
add_test(NAME OpenFileTest_0 COMMAND $<TARGET_FILE:MedianFilter>)
set_tests_properties(OpenFileTest_0 PROPERTIES WILL_FAIL true )


# Tests checking that the program cannot run without 4 arguments
add_test(NAME OpenFileTest_1 COMMAND $<TARGET_FILE:MedianFilter>
  ${Input}
)
set_tests_properties(OpenFileTest_1 PROPERTIES WILL_FAIL true )

add_test(NAME OpenFileTest_2 COMMAND $<TARGET_FILE:MedianFilter>
  ${Input}
  ${FakeOutput}
)
set_tests_properties(OpenFileTest_2 PROPERTIES WILL_FAIL true )

add_test(NAME OpenFileTest_3 COMMAND $<TARGET_FILE:MedianFilter>
  ${Input}
  ${FakeOutput}
  -r
)
set_tests_properties(OpenFileTest_3 PROPERTIES WILL_FAIL true )
 

# Test checking that the radius value cannot go below 0
add_test(NAME RadiusValueMin COMMAND $<TARGET_FILE:MedianFilter>
  ${Input}
  ${FakeOutput}
  -r -5
)
set_tests_properties( RadiusValueMin PROPERTIES WILL_FAIL true )

# Test checking that the radius value cannot go above 6
add_test(NAME RadiusValueMax COMMAND $<TARGET_FILE:MedianFilter>
  ${Input}
  ${FakeOutput}
  -r 8
)
set_tests_properties( RadiusValueMax PROPERTIES WILL_FAIL true )


#Test checking that the programm cannot run with a wrong input
add_test(NAME MedianFilterWrongInputFileName COMMAND $<TARGET_FILE:MedianFilter>
  WrongInput.nrrd
  ${FakeOutput}
  -r 3
)
set_tests_properties( MedianFilterWrongInputFileName PROPERTIES WILL_FAIL true )


# Tests checking that that the output image is what it's expected
add_test(NAME MedianFilterRadius2 COMMAND $<TARGET_FILE:MedianFilterTest>
  --compare
    ${Reference1}
    ${RadiusValue2}
  ModuleEntryPoint
    ${Input}
    ${RadiusValue2}
    -r 2
  )

add_test(NAME MedianFilterRadius4 COMMAND $<TARGET_FILE:MedianFilterTest>
  --compare
    ${Reference2}
    ${RadiusValue4}
  ModuleEntryPoint
    ${Input}
    ${RadiusValue4}
    -r 4
  )

# Test for the command --help
add_test(NAME PrintHelp COMMAND $<TARGET_FILE:MedianFilter> --help)



