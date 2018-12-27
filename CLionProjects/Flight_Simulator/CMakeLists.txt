cmake_minimum_required(VERSION 3.12)
project(Flight_Simulator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(Flight_Simulator main.cpp ReadData.h Command.h openDataServerCommand.h Minus.h Div.h EvaluateExp.cpp EvaluateExp.h Plus.h Mult.h Expression.h BinaryExpression.h Number.h CommandExpression.h conditionParser.h loopCommand.h ifCommand.h endOfLoopCommand.h ConnectCommand.h PrintCommand.h varCommand.h openDataServerCommand.cpp DataReaderServer.cpp DataReaderServer.h global.cpp global.h ConnectCommand.cpp sleepCommand.h sleepCommand.cpp varCommand.cpp EntercCommand.cpp EntercCommand.h)