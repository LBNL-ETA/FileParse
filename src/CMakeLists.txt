set( CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON )

add_library( ${LIB_NAME}
        FP_Base.hxx
		FP_Common.hxx
		FP_Enum.hxx
		FP_Map.hxx
		FP_Optional.hxx
		FP_Set.hxx
		FP_StringConversion.hxx
		FP_Variant.hxx
		FP_Vector.hxx
		FP_XMLNodeAdapter.cxx
		FP_XMLNodeAdapter.hxx)

if(NOT "${fPIC}")
  set(fPIC ON)
endif()

if(fPIC)
  set_property(TARGET ${LIB_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(${LIB_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
if ( MSVC )
    target_compile_options(${LIB_NAME} PRIVATE /W4 /WX)
endif()

target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)
target_link_libraries(${LIB_NAME} PUBLIC xmlParser)




