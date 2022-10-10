set(src_dirs    
                ai
                camera)

set(include_dirs    
                    ai
                    camera)

set(requires    esp32-camera
                esp-dl
                sra-board-component)

idf_component_register(REQUIRES ${requires} SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs})

component_compile_options(-ffast-math -O3)
