#--------------------------------------------------------------------------
# NeckGraphics project
#--------------------------------------------------------------------------

PROJECT(NeckGraphics)
FILE(GLOB neckgraphics_headers code/*.h)
FILE(GLOB neckgraphics_sources code/*.cc)

SET(files_neckgraphics ${neckgraphics_headers} ${neckgraphics_sources})
SOURCE_GROUP("neckgraphics" FILES ${files_neckgraphics})

ADD_EXECUTABLE(NeckGraphics ${files_neckgraphics})
TARGET_LINK_LIBRARIES(NeckGraphics core render)
ADD_DEPENDENCIES(NeckGraphics core render)
