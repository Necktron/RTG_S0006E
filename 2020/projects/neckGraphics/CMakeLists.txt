#--------------------------------------------------------------------------
# neckGraphics project
#--------------------------------------------------------------------------

PROJECT(neckGraphics)
FILE(GLOB neckGraphics_headers code/*.h)
FILE(GLOB neckGraphics_sources code/*.cc)

SET(files_neckGraphics ${neckGraphics_headers} ${neckGraphics_sources})
SOURCE_GROUP("neckGraphics" FILES ${files_neckGraphics})

ADD_EXECUTABLE(neckGraphics ${files_neckGraphics})
TARGET_LINK_LIBRARIES(neckGraphics core render)
ADD_DEPENDENCIES(neckGraphics core render)