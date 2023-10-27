# Gather our source files in this directory.
set(
  gazprea_src_files
  "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Scope.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Symbol.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/AST.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTBuilder.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTPass.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/CodeGenPass.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/DefRef.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/FunctionErrorPass.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/AssignStatement.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/AtomNodes.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/BinaryExpr.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/Block.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/BuiltInCall.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/ConditionStatement.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/DeclareStatement.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/DomainExpr.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/ExtraLeafNodes.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/FileNode.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/FilterExpr.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/FunctionNodes.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/GeneratorExpr.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/IdNode.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/Loop.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/ProcedureCall.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/ProcedureDecl.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/ProcedureParam.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/Stream.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/TupleType.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/TypeCast.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/TypeDef.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/TypeNode.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ASTNodes/UnaryExpr.cpp"
  )

# Build our executable from the source files.
add_executable(gazc ${gazprea_src_files})
target_include_directories(gazc PUBLIC ${ANTLR_GEN_DIR})

# Ensure that the antlr4-runtime is available.
add_dependencies(gazc antlr)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs core)

# Add the antlr runtime and parser as libraries to link.
target_link_libraries(gazc parser antlr4-runtime ${llvm_libs})

# Symbolic link our executable to the base directory so we don't have to go searching for it.
symlink_to_bin("gazc")
