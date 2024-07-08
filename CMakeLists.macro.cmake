# добавление зависимости в проект с git репозитория
# @param name - название папки
# @param url - url репозитория
macro(DOWNLOAD_REPOSITORY_FROM_GIT name branch_name url)

    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libs)
        message("create directory " ${CMAKE_CURRENT_SOURCE_DIR}/libs)
        execute_process(COMMAND mkdir libs
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()

    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libs/${name})
        execute_process(COMMAND git clone --branch ${branch_name} ${url}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs)
    endif()

endmacro()


# добавление зависимости в проект с git репозитория
# @param name - название папки
# @param url - url репозитория
macro(DOWNLOAD_REPOSITORY_FROM_GIT_RECURSIVE name branch_name url)

    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libs)
        message("create directory " ${CMAKE_CURRENT_SOURCE_DIR}/libs)
        execute_process(COMMAND mkdir libs
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()

    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libs/${name})
        execute_process(COMMAND git clone --recursive --branch ${branch_name} ${url}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs)
    endif()

        if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libs/${name}/CMakeLists.txt)
            message("add subdirectory " ${CMAKE_CURRENT_SOURCE_DIR}/libs/${name})
            add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/${name})
        endif ()

endmacro()

# добавление подмодуля в проект с git репозитория
# @param name - название папки
# @param url - url репозитория
macro(DOWNLOAD_SUBMODULE_FROM_GIT name branch_name url)

    if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/submodules)
        message("create directory " ${CMAKE_CURRENT_SOURCE_DIR}/submodules)
        execute_process(COMMAND mkdir submodules
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif ()

    if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/submodules/${name})
        execute_process(COMMAND git clone --branch ${branch_name} ${url}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules)
    endif ()

    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/submodules/${name}/CMakeLists.txt)
        message("add subdirectory " ${CMAKE_CURRENT_SOURCE_DIR}/submodules/${name})
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodules/${name})
    endif ()
endmacro()


# добавление cmake файлов с инструкциями по сборке бинарников скачаных с гита библиотек
macro(BUILD_ALL_DOWNLOADED_LIBRARIES)
    file(GLOB files "${PROJECT_SOURCE_DIR}/libsCmakeDir/*.cmake")
    foreach(file ${files})
        include(${file})
    endforeach()
endmacro()

# создание библиотеки из своих исходников
macro(BUILD_LIBRARY_FROM_OWN_CODE libraryName rel_path_to_source_dir)

    if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/${rel_path_to_source_dir}/${libraryName}.h")
        message("create header for ${libraryName}")
        file(GLOB_RECURSE cpp_files "${CMAKE_CURRENT_LIST_DIR}/${rel_path_to_source_dir}/*.cpp")
        include_directories(${CMAKE_CURRENT_SOURCE_DIR})
        add_library(${libraryName} SHARED ${cpp_files})
        set(header_file "${CMAKE_CURRENT_LIST_DIR}/${rel_path_to_source_dir}/${libraryName}.h")
        file(GLOB_RECURSE headers_list "${CMAKE_CURRENT_LIST_DIR}/${rel_path_to_source_dir}/*.h")
        set(headers_string "#pragma ones \n")
        foreach (header ${headers_list})
            if (NOT ${header_file} MATCHES ${header})
                set(headers_string ${headers_string} "#include \"${header}\"\n")
            endif ()
        endforeach ()
        string(REPLACE ";" " " headers_string ${headers_string})
        # string(REPLACE "//" "/" headers_string ${headers_string})
        file(GENERATE OUTPUT "${header_file}" CONTENT "${headers_string}")
    else ()
        file(GLOB_RECURSE cpp_files "${CMAKE_CURRENT_LIST_DIR}/${rel_path_to_source_dir}/*.cpp")
        include_directories(${CMAKE_CURRENT_SOURCE_DIR})
        add_library(${libraryName} SHARED ${cpp_files})
    endif ()
endmacro()

# парсинг файла с конфигурацией для гита
macro(READ_GIT_TOKEN)
    # Read the JSON file.
    file(READ ${CMAKE_CURRENT_SOURCE_DIR}/token.json DATA)
    string(JSON CUR_TOKEN GET ${DATA} token)
    SET(GIT_TOKEN ${CUR_TOKEN})
    message("git token: " ${GIT_TOKEN})
endmacro()
