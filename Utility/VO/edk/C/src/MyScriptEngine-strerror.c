/**
 * @file MyScriptEngine-strerror.c
 * 
 */

#include "MyScriptEngine-strerror.h"
#include <c/MyScriptEngine.h>
#include <c/MyScriptHWR.h>
#include <c/MyScriptInkSearch.h>
#include <c/MyScriptShape.h>
#include <c/MyScriptEquation.h>
#include <c/MyScriptAnalyzer.h>
#include <c/MyScriptMusic.h>


char const* strMyScriptError(int error)
{
#define __CASE_FROM_ERROR_CODE(x) case VO_##x: return #x
  switch (error)
  {
#ifdef C_MYSCRIPTENGINE_H
  __CASE_FROM_ERROR_CODE(NO_ERROR);
  __CASE_FROM_ERROR_CODE(INVALID_ARGUMENT);
  __CASE_FROM_ERROR_CODE(INVALID_OPERATION);
  __CASE_FROM_ERROR_CODE(INVALID_STATE);
  __CASE_FROM_ERROR_CODE(RUNTIME_ERROR);
  __CASE_FROM_ERROR_CODE(NO_SUCH_REFERENCE);
  __CASE_FROM_ERROR_CODE(NO_SUCH_ENGINE);
  __CASE_FROM_ERROR_CODE(NO_SUCH_OBJECT);
  __CASE_FROM_ERROR_CODE(INVALID_VERSION);
  __CASE_FROM_ERROR_CODE(INVALID_CERTIFICATE);
  __CASE_FROM_ERROR_CODE(INDEX_OUT_OF_BOUNDS);
  __CASE_FROM_ERROR_CODE(INVALID_OBJECT);
  __CASE_FROM_ERROR_CODE(INVALID_OPTION);
  __CASE_FROM_ERROR_CODE(INVALID_SIZE);
  __CASE_FROM_ERROR_CODE(NO_SUCH_ELEMENT);
  __CASE_FROM_ERROR_CODE(INVALID_TRAINING_SET);
  __CASE_FROM_ERROR_CODE(INVALID_USER_BUFFER);
  __CASE_FROM_ERROR_CODE(INVALID_CALLBACK);
  __CASE_FROM_ERROR_CODE(NO_SUCH_TYPE);
  __CASE_FROM_ERROR_CODE(TYPE_NOT_CONCRETE);
  __CASE_FROM_ERROR_CODE(NO_SUCH_CONSTRUCTOR);
  __CASE_FROM_ERROR_CODE(NO_SUCH_INTERFACE);
  __CASE_FROM_ERROR_CODE(NO_SUCH_PROPERTY);
  __CASE_FROM_ERROR_CODE(READ_ONLY_PROPERTY);
  __CASE_FROM_ERROR_CODE(UNSUPPORTED_SERIALIZATION);
  __CASE_FROM_ERROR_CODE(LIMIT_EXCEEDED);
  __CASE_FROM_ERROR_CODE(NOT_COMPILED);
  __CASE_FROM_ERROR_CODE(MODIFICATION_ACCESS_DENIED);
  __CASE_FROM_ERROR_CODE(UNMATCHED_INPUT_UNIT);
  __CASE_FROM_ERROR_CODE(OUT_OF_MEMORY);
  __CASE_FROM_ERROR_CODE(IO_FAILURE);
  __CASE_FROM_ERROR_CODE(PREMATURE_END_OF_DATA);
  __CASE_FROM_ERROR_CODE(INTERNAL_ERROR);
  __CASE_FROM_ERROR_CODE(CANCELED);
  __CASE_FROM_ERROR_CODE(NO_SUCH_FILE);
#endif // end of: #ifdef C_MYSCRIPTENGINE_H

#ifdef C_MYSCRIPTHWR_H
  __CASE_FROM_ERROR_CODE(MISSING_ALPHABET_KNOWLEDGE);
  __CASE_FROM_ERROR_CODE(MISSING_SOURCE);
  __CASE_FROM_ERROR_CODE(CHAR_STROKE_LIMIT_EXCEEDED);
  __CASE_FROM_ERROR_CODE(REGEX_SUBEXP_IMBALANCE);
  __CASE_FROM_ERROR_CODE(REGEX_UNMATCHED_OPEN_SET);
  __CASE_FROM_ERROR_CODE(REGEX_UNMATCHED_OPEN_REF);
  __CASE_FROM_ERROR_CODE(REGEX_TRAILING_ESCAPE);
  __CASE_FROM_ERROR_CODE(REGEX_INVALID_CHARACTER);
  __CASE_FROM_ERROR_CODE(REGEX_INVALID_REFERENCE);
  __CASE_FROM_ERROR_CODE(REGEX_UNMATCHED_CLOSE_SET);
  __CASE_FROM_ERROR_CODE(REGEX_UNMATCHED_CLOSE_REF);
  __CASE_FROM_ERROR_CODE(REGEX_UNESCAPED_OPERATOR);
  __CASE_FROM_ERROR_CODE(INPUT_LIMIT_EXCEEDED);
#endif // end of: #ifdef C_MYSCRIPTHWR_H

#ifdef C_MYSCRIPTINKSEARCH_H
  __CASE_FROM_ERROR_CODE(MISSING_INDEX);
  __CASE_FROM_ERROR_CODE(MISSING_QUERY);
#endif // end of: #ifdef C_MYSCRIPTINKSEARCH_H

#ifdef C_MYSCRIPTSHAPE_H
  __CASE_FROM_ERROR_CODE(MISSING_SHAPE_KNOWLEDGE);
  __CASE_FROM_ERROR_CODE(UNMATCHED_SHAPE_SEGMENT);
#endif // end of: #ifdef C_MYSCRIPTSHAPE_H

#ifdef C_MYSCRIPTEQUATION_H
  __CASE_FROM_ERROR_CODE(MISSING_EQUATION_ALPHABET_KNOWLEDGE);
  __CASE_FROM_ERROR_CODE(MISSING_EQUATION_GRAMMAR);
#endif // end of: #ifdef C_MYSCRIPTEQUATION_H

#ifdef C_MYSCRIPTANALYZER_H
  __CASE_FROM_ERROR_CODE(MISSING_ANALYZER_KNOWLEDGE);
#endif // end of: #ifdef C_MYSCRIPTANALYZER_H

#ifdef C_MYSCRIPTMUSIC_H
  __CASE_FROM_ERROR_CODE(MISSING_MUSIC_ALPHABET_KNOWLEDGE);
  __CASE_FROM_ERROR_CODE(MISSING_MUSIC_GRAMMAR);
  __CASE_FROM_ERROR_CODE(MISSING_MUSIC_STAFF);
#endif // end of: #ifdef C_MYSCRIPTMUSIC_H

  default:
    return "<<UNKNOWN>>";
  }
#undef __CASE_FROM_ERROR_CODE
}
