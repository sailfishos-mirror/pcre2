/*************************************************
*      Perl-Compatible Regular Expressions       *
*************************************************/

/* PCRE is a library of functions to support regular expressions whose syntax
and semantics are as close as possible to those of the Perl 5 language.

                       Written by Philip Hazel
     Original API code Copyright (c) 1997-2012 University of Cambridge
          New API code Copyright (c) 2016-2024 University of Cambridge

-----------------------------------------------------------------------------
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    * Neither the name of the University of Cambridge nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------------
*/


/* This module contains the mode-dependent code which is used by pcre2test.c.
It is #included in pcre2test.c at each supported code unit width, with
PCRE2_SUFFIX set appropriately, just like the functions that comprise the
library. */


/* ---------------- Mode-dependent variables -------------------*/

// XXX fix

// #ifdef SUPPORT_PCRE2_8
// XXX init all to NULL
// static pcre2_code_8             *compiled_code8;
// static pcre2_general_context_8  *general_context8, *general_context_copy8;
// static pcre2_compile_context_8  *pat_context8, *default_pat_context8;
// static pcre2_convert_context_8  *con_context8, *default_con_context8;
// static pcre2_match_context_8    *dat_context8, *default_dat_context8;
// static pcre2_match_data_8       *match_data8;
// #endif

// #ifdef SUPPORT_PCRE2_16
// static pcre2_code_16            *compiled_code16;
// static pcre2_general_context_16 *general_context16, *general_context_copy16;
// static pcre2_compile_context_16 *pat_context16, *default_pat_context16;
// static pcre2_convert_context_16 *con_context16, *default_con_context16;
// static pcre2_match_context_16   *dat_context16, *default_dat_context16;
// static pcre2_match_data_16      *match_data16;
// static PCRE2_SIZE pbuffer16_size = 0;   /* Set only when needed */
// static uint16_t *pbuffer16 = NULL;
// #endif

// #ifdef SUPPORT_PCRE2_32
// static pcre2_code_32            *compiled_code32;
// static pcre2_general_context_32 *general_context32, *general_context_copy32;
// static pcre2_compile_context_32 *pat_context32, *default_pat_context32;
// static pcre2_convert_context_32 *con_context32, *default_con_context32;
// static pcre2_match_context_32   *dat_context32, *default_dat_context32;
// static pcre2_match_data_32      *match_data32;
// static PCRE2_SIZE pbuffer32_size = 0;   /* Set only when needed */
// static uint32_t *pbuffer32 = NULL;
// #endif


/* ---------------- Macros that work in all modes ----------------- */

// XXX fix/remove

// #define CAST8VAR(x) CASTVAR(uint8_t *, x)
// #define SET(x,y) SETOP(x,y,=)
// #define SETPLUS(x,y) SETOP(x,y,+=)
// #define strlen8(x) strlen((char *)x)

#define PCRE2_SPTR  PCRE2_SUFFIX(PCRE2_SPTR)
#define pchars      PCRE2_SUFFIX(pchars)
#define ptrunc      PCRE2_SUFFIX(ptrunc)


/* ---------------- Mode-dependent, runtime-testing macros ------------------*/

/* Define macros for variables and functions that must be selected dynamically
depending on the mode setting (8, 16, 32). These are dependent on which modes
are supported. */

#define CASTFLD(t,a,b) (t)(G(a,8)->b)
#define CASTVAR(t,x) (t)G(x,8)
#define CODE_UNIT(a,b) (uint32_t)(((PCRE2_SPTR8)(a))[b])
#define CONCTXCPY(a,b) memcpy(G(a,8),G(b,8),sizeof(pcre2_convert_context_8))
#define CONVERT_COPY(a,b,c) memcpy(G(a,8),(char *)b, c)
#define DATCTXCPY(a,b) memcpy(G(a,8),G(b,8),sizeof(pcre2_match_context_8))
#define FLD(a,b) G(a,8)->b
#define PATCTXCPY(a,b) memcpy(G(a,8),G(b,8),sizeof(pcre2_compile_context_8))
#define PCHARS(lv, p, offset, len, utf, f) \
  lv = pchars8((PCRE2_SPTR8)(p)+offset, len, utf, f)
#define PCHARSV(p, offset, len, utf, f) \
  (void)pchars8((PCRE2_SPTR8)(p)+offset, len, utf, f)
#define PTRUNCV(p, p_len, offset, left, utf, f) \
  ptrunc8((PCRE2_SPTR8)(p), p_len, offset, left, utf, f)
#define PCRE2_CALLOUT_ENUMERATE(a,b,c) \
   a = pcre2_callout_enumerate_8(compiled_code8, \
     (int (*)(struct pcre2_callout_enumerate_block_8 *, void *))b,c)
#define PCRE2_CODE_COPY_FROM_VOID(a,b) G(a,8) = pcre2_code_copy_8(b)
#define PCRE2_CODE_COPY_TO_VOID(a,b) a = (void *)pcre2_code_copy_8(G(b,8))
#define PCRE2_CODE_COPY_WITH_TABLES_TO_VOID(a,b) a = (void *)pcre2_code_copy_with_tables_8(G(b,8))
#define PCRE2_COMPILE(a,b,c,d,e,f,g) G(a,8) = pcre2_compile_8(b,c,d,e,f,g)
#define PCRE2_CONFIG(lv,a,b) lv = pcre2_config_8(a,b)
#define PCRE2_CONFIGV(a,b) (void)pcre2_config_8(a,b)
#define PCRE2_CONVERTED_PATTERN_FREE(a) \
  pcre2_converted_pattern_free_8((PCRE2_UCHAR8 *)a)
#define PCRE2_DFA_MATCH(a,b,c,d,e,f,g,h,i,j) \
  a = pcre2_dfa_match_8(G(b,8),(PCRE2_SPTR8)c,d,e,f,G(g,8),h,i,j)
#define PCRE2_GET_ERROR_MESSAGE(r,a) \
  r = pcre2_get_error_message_8(a,(PCRE2_UCHAR8 *)errorbuffer,errorbuffer_size)
#define PCRE2_GET_MATCH_DATA_HEAPFRAMES_SIZE(r,a) \
  r = pcre2_get_match_data_heapframes_size_8(G(a,8))
#define PCRE2_GET_OVECTOR_COUNT(a,b) a = pcre2_get_ovector_count_8(G(b,8))
#define PCRE2_GET_STARTCHAR(a,b) a = pcre2_get_startchar_8(G(b,8))
#define PCRE2_NEXT_MATCH(a,b,c,d) a = pcre2_next_match_8(G(b,8),c,d)
#define PCRE2_JIT_COMPILE(r,a,b) r = pcre2_jit_compile_8(G(a,8),b)
#define PCRE2_JIT_FREE_UNUSED_MEMORY(a) pcre2_jit_free_unused_memory_8(G(a,8))
#define PCRE2_JIT_MATCH(a,b,c,d,e,f,g,h) \
  a = pcre2_jit_match_8(G(b,8),(PCRE2_SPTR8)c,d,e,f,G(g,8),h)
#define PCRE2_JIT_STACK_CREATE(a,b,c,d) \
  a = (PCRE2_JIT_STACK *)pcre2_jit_stack_create_8(b,c,d);
#define PCRE2_JIT_STACK_ASSIGN(a,b,c) \
  pcre2_jit_stack_assign_8(G(a,8),(pcre2_jit_callback_8)b,c);
#define PCRE2_JIT_STACK_FREE(a) pcre2_jit_stack_free_8((pcre2_jit_stack_8 *)a);
#define PCRE2_MAKETABLES(a,c) a = pcre2_maketables_8(G(c,8))
#define PCRE2_MAKETABLES_FREE(c,a) pcre2_maketables_free_8(G(c,8),a)
#define PCRE2_MATCH(a,b,c,d,e,f,g,h) \
  a = pcre2_match_8(G(b,8),(PCRE2_SPTR8)c,d,e,f,G(g,8),h)
#define PCRE2_MATCH_DATA_CREATE(a,b,c) G(a,8) = pcre2_match_data_create_8(b,G(c,8))
#define PCRE2_MATCH_DATA_CREATE_FROM_PATTERN(a,b,c) \
  G(a,8) = pcre2_match_data_create_from_pattern_8(G(b,8),G(c,8))
#define PCRE2_MATCH_DATA_FREE(a) pcre2_match_data_free_8(G(a,8))
#define PCRE2_PATTERN_CONVERT(a,b,c,d,e,f,g) a = pcre2_pattern_convert_8(G(b,8),c,d,(PCRE2_UCHAR8 **)e,f,G(g,8))
#define PCRE2_PATTERN_INFO(a,b,c,d) a = pcre2_pattern_info_8(G(b,8),c,d)
#define PCRE2_PRINTINT(a) pcre2_printint_8(compiled_code8,outfile,a)
#define PCRE2_SERIALIZE_DECODE(r,a,b,c,d) \
  r = pcre2_serialize_decode_8((pcre2_code_8 **)a,b,c,G(d,8))
#define PCRE2_SERIALIZE_ENCODE(r,a,b,c,d,e) \
  r = pcre2_serialize_encode_8((const pcre2_code_8 **)a,b,c,d,G(e,8))
#define PCRE2_SERIALIZE_FREE(a) pcre2_serialize_free_8(a)
#define PCRE2_SERIALIZE_GET_NUMBER_OF_CODES(r,a) \
  r = pcre2_serialize_get_number_of_codes_8(a)
#define PCRE2_SET_CALLOUT(a,b,c) \
  pcre2_set_callout_8(G(a,8),(int (*)(pcre2_callout_block_8 *, void *))b,c)
#define PCRE2_SET_CHARACTER_TABLES(a,b) pcre2_set_character_tables_8(G(a,8),b)
#define PCRE2_SET_COMPILE_RECURSION_GUARD(a,b,c) \
  pcre2_set_compile_recursion_guard_8(G(a,8),b,c)
#define PCRE2_SET_DEPTH_LIMIT(a,b) pcre2_set_depth_limit_8(G(a,8),b)
#define PCRE2_SET_GLOB_ESCAPE(r,a,b) r = pcre2_set_glob_escape_8(G(a,8),b)
#define PCRE2_SET_GLOB_SEPARATOR(r,a,b) r = pcre2_set_glob_separator_8(G(a,8),b)
#define PCRE2_SET_HEAP_LIMIT(a,b) pcre2_set_heap_limit_8(G(a,8),b)
#define PCRE2_SET_MATCH_LIMIT(a,b) pcre2_set_match_limit_8(G(a,8),b)
#define PCRE2_SET_MAX_PATTERN_COMPILED_LENGTH(a,b) pcre2_set_max_pattern_compiled_length_8(G(a,8),b)
#define PCRE2_SET_MAX_PATTERN_LENGTH(a,b) pcre2_set_max_pattern_length_8(G(a,8),b)
#define PCRE2_SET_MAX_VARLOOKBEHIND(a,b) pcre2_set_max_varlookbehind_8(G(a,8),b)
#define PCRE2_SET_OFFSET_LIMIT(a,b) pcre2_set_offset_limit_8(G(a,8),b)
#define PCRE2_SET_PARENS_NEST_LIMIT(a,b) pcre2_set_parens_nest_limit_8(G(a,8),b)
#define PCRE2_SET_SUBSTITUTE_CALLOUT(a,b,c) \
  pcre2_set_substitute_callout_8(G(a,8), \
    (int (*)(pcre2_substitute_callout_block_8 *, void *))b,c)
#define PCRE2_SET_SUBSTITUTE_CASE_CALLOUT(a,b,c) \
  pcre2_set_substitute_case_callout_8(G(a,8),G(b,8),c)
#define PCRE2_SET_SUBSTITUTE_CASE_CALLOUT_NULL(a) \
  pcre2_set_substitute_case_callout_8(G(a,8),NULL,NULL)
#define PCRE2_SUBSTITUTE(a,b,c,d,e,f,g,h,i,j,k,l) \
  a = pcre2_substitute_8(G(b,8),(PCRE2_SPTR8)c,d,e,f,G(g,8),h, \
    (PCRE2_SPTR8)i,j,(PCRE2_UCHAR8 *)k,l)
#define PCRE2_SUBSTRING_COPY_BYNAME(a,b,c,d,e) \
  a = pcre2_substring_copy_byname_8(G(b,8),G(c,8),(PCRE2_UCHAR8 *)d,e)
#define PCRE2_SUBSTRING_COPY_BYNUMBER(a,b,c,d,e) \
  a = pcre2_substring_copy_bynumber_8(G(b,8),c,(PCRE2_UCHAR8 *)d,e)
#define PCRE2_SUBSTRING_FREE(a) pcre2_substring_free_8((PCRE2_UCHAR8 *)a)
#define PCRE2_SUBSTRING_GET_BYNAME(a,b,c,d,e) \
  a = pcre2_substring_get_byname_8(G(b,8),G(c,8),(PCRE2_UCHAR8 **)d,e)
#define PCRE2_SUBSTRING_GET_BYNUMBER(a,b,c,d,e) \
  a = pcre2_substring_get_bynumber_8(G(b,8),c,(PCRE2_UCHAR8 **)d,e)
#define PCRE2_SUBSTRING_LENGTH_BYNAME(a,b,c,d) \
    a = pcre2_substring_length_byname_8(G(b,8),G(c,8),d)
#define PCRE2_SUBSTRING_LENGTH_BYNUMBER(a,b,c,d) \
    a = pcre2_substring_length_bynumber_8(G(b,8),c,d)
#define PCRE2_SUBSTRING_LIST_GET(a,b,c,d) \
  a = pcre2_substring_list_get_8(G(b,8),(PCRE2_UCHAR8 ***)c,d)
#define PCRE2_SUBSTRING_LIST_FREE(a) \
  pcre2_substring_list_free_8((PCRE2_UCHAR8 **)a)
#define PCRE2_SUBSTRING_NUMBER_FROM_NAME(a,b,c) \
  a = pcre2_substring_number_from_name_8(G(b,8),G(c,8));
#define PTR(x) (void *)G(x,8)
#define SETFLD(x,y,z) G(x,8)->y = z
#define SETOP(x,y,z) G(x,8) z y
#define SETCASTPTR(x,y) G(x,8) = (uint8_t *)(y)
#define STRLEN(p) strlen((char *)p)
#define SUB1(a,b) G(a,8)(G(b,8))
#define SUB2(a,b,c) G(a,8)(G(b,8),G(c,8))
#define TEST(x,r,y) (G(x,8) r (y))
#define TESTFLD(x,f,r,y) (G(x,8)->f r (y))


/* ----- End of mode-specific function call macros ----- */



/*************************************************
*    Find length of 0-terminated 16-bit string   *
*************************************************/

static size_t PCRE2_SUFFIX(strlen)(PCRE2_SPTR p)
{
#if PCRE2_CODE_UNIT_WIDTH == 8
return strlen(p);
#else
PCRE2_SPTR pp = p;
while (*pp != 0) pp++;
return pp - p;
#endif /* PCRE_CODE_UNIT_WIDTH == 8 */
}



/*************************************************
*           Print character string               *
*************************************************/

/* Must handle Unicode strings in UTF mode. Yields number of characters printed.
For printing *MARK strings, a negative length is given, indicating that the
length is in the first code unit. If handed a NULL file, this function just
counts chars without printing (because pchar() does that). */

static int pchars(PCRE2_SPTR p, ptrdiff_t length, BOOL utf, FILE *f)
{
#if PCRE2_CODE_UNIT_WIDTH == 8 || PCRE2_CODE_UNIT_WIDTH == 16
PCRE2_SPTR end;
uint32_t c = 0;
int yield = 0;
if (length < 0) length = *p++;
end = p + length;
while (length-- > 0)
  {
  if (utf)
    {
    int rc = G(G(utf,PCRE2_CODE_UNIT_WIDTH),_to_ord)(p, end, &c);
    if (rc > 0 && rc <= length + 1)   /* Mustn't run over the end */
      {
      length -= rc - 1;
      p += rc;
      yield += pchar(c, utf, f);
      continue;
      }
    }
  c = *p++;
  yield += pchar(c, utf, f);
  }

return yield;

#else
int yield = 0;
if (length < 0) length = *p++;
while (length-- > 0)
  {
  uint32_t c = *p++;
  yield += pchar(c, utf, f);
  }
return yield;

#endif
}



/*************************************************
*        Print truncated character string        *
*************************************************/

/* Must handle Unicode strings in UTF mode. Passed the total input string, and
the offset to print from/to. If left is true, prints up to the offset,
truncated; otherwise prints from the offset to the right, truncated. */

#if PCRE2_CODE_UNIT_WIDTH == 8
static void ptrunc8(PCRE2_SPTR8 p, size_t p_len, size_t offset, BOOL left,
  BOOL utf, FILE *f)
{
PCRE2_SPTR8 start = p + offset;
PCRE2_SPTR8 end = p + offset;
size_t printed = 0;

if (left)
  {
  while (start > p && printed < 10)
    {
    printed++;
    start--;
    if (utf)
      { while(start > p && (*start & 0xc0u) == 0x80u) start--; }
    }
  }
else
  {
  while (end < p + p_len && printed < 10)
    {
    printed++;
    end++;
    if (utf)
      { while(end < p + p_len && (*end & 0xc0u) == 0x80u) end++; }
    }
  }

if (left && start > p) fprintf(f, "...");
for (; start < end; start++) fprintf(f, "%c", CHAR_OUTPUT(*start));
if (!left && end < p + p_len) fprintf(f, "...");
}

#elif PCRE2_CODE_UNIT_WIDTH == 16
static void ptrunc16(PCRE2_SPTR16 p, size_t p_len, size_t offset, BOOL left,
  BOOL utf, FILE *f)
{
PCRE2_SPTR16 start = p + offset;
PCRE2_SPTR16 end = p + offset;
size_t printed = 0;

if (left)
  {
  while (start > p && printed < 10)
    {
    printed++;
    start--;
    if (utf)
      { while(start > p && (*start & 0xfc00u) == 0xdc00u) start--; }
    }
  }
else
  {
  while (end < p + p_len && printed < 10)
    {
    printed++;
    end++;
    if (utf)
      { while(end < p + p_len && (*end & 0xfc00u) == 0xdc00u) end++; }
    }
  }

if (left && start > p) fprintf(f, "...");
while (start < end)
  {
  uint32_t c;
  int rc = utf16_to_ord(start, end, &c);
  if (rc < 0) c = *start++;
  else start += rc;
  if (c > 0xff || (utf && c > 0x7f))
    {
    uint8_t u8buff[6];
    int clen = ord_to_utf8(c, u8buff);
    fprintf(f, "%.*s", clen, u8buff);
    continue;
    }
  fputc((int)c, f);
  }
if (!left && end < p + p_len) fprintf(f, "...");
}

#elif PCRE2_CODE_UNIT_WIDTH == 32
static void ptrunc32(PCRE2_SPTR32 p, size_t p_len, size_t offset, BOOL left,
  BOOL utf, FILE *f)
{
PCRE2_SPTR32 start = p + offset;
PCRE2_SPTR32 end = p + offset;

if (left)
  {
  start -= (offset > 10)? 10 : offset;
  }
else
  {
  end += (p + p_len - end > 10)? 10 : p + p_len - end;
  }

if (left && start > p) fprintf(f, "...");
while (start < end)
  {
  uint32_t c = *start++;
  if (c > 0xff || (utf && c > 0x7f))
    {
    uint8_t u8buff[6];
    int clen = ord_to_utf8(c, u8buff);
    fprintf(f, "%.*s", clen, u8buff);
    continue;
    }
  fputc((int)c, f);
  }
if (!left && end < p + p_len) fprintf(f, "...");
}
#endif



#if PCRE2_CODE_UNIT_WIDTH == 16
/*************************************************
*           Convert string to 16-bit             *
*************************************************/

/* In UTF mode the input is always interpreted as a string of UTF-8 bytes using
the original UTF-8 definition of RFC 2279, which allows for up to 6 bytes, and
code values from 0 to 0x7fffffff. However, values greater than the later UTF
limit of 0x10ffff cause an error. In non-UTF mode the input is interpreted as
UTF-8 if the utf8_input modifier is set, but an error is generated for values
greater than 0xffff.

If all the input bytes are ASCII, the space needed for a 16-bit string is
exactly double the 8-bit size. Otherwise, the size needed for a 16-bit string
is no more than double, because up to 0xffff uses no more than 3 bytes in UTF-8
but possibly 4 in UTF-16. Higher values use 4 bytes in UTF-8 and up to 4 bytes
in UTF-16. The result is always left in pbuffer16. Impose a minimum size to
save repeated re-sizing.

Note that this function does not object to surrogate values. This is
deliberate; it makes it possible to construct UTF-16 strings that are invalid,
for the purpose of testing that they are correctly faulted.

Arguments:
  p          points to a byte string
  utf        true in UTF mode
  lenptr     points to number of bytes in the string (excluding trailing zero)

Returns:     0 on success, with the length updated to the number of 16-bit
               data items used (excluding the trailing zero)
             OR -1 if a UTF-8 string is malformed
             OR -2 if a value > 0x10ffff is encountered in UTF mode
             OR -3 if a value > 0xffff is encountered when not in UTF mode
*/

static int
to16(uint8_t *p, int utf, PCRE2_SIZE *lenptr)
{
uint16_t *pp;
PCRE2_SIZE len = *lenptr;

if (pbuffer16_size < 2*len + 2)
  {
  if (pbuffer16 != NULL) free(pbuffer16);
  pbuffer16_size = 2*len + 2;
  if (pbuffer16_size < 4096) pbuffer16_size = 4096;
  pbuffer16 = (uint16_t *)malloc(pbuffer16_size);
  if (pbuffer16 == NULL)
    {
    fprintf(stderr, "pcre2test: malloc(%" SIZ_FORM ") failed for pbuffer16\n",
      pbuffer16_size);
    exit(1);
    }
  }

pp = pbuffer16;
if (!utf && (pat_patctl.control & CTL_UTF8_INPUT) == 0)
  {
  for (; len > 0; len--) *pp++ = *p++;
  }

else while (len > 0)
  {
  uint32_t c;
  const uint8_t *end = p + len;
  int chlen = utf8_to_ord(p, end, &c);
  if (chlen <= 0) return -1;
  if (!utf && c > 0xffff) return -3;
  if (c > 0x10ffff) return -2;
  p += chlen;
  len -= chlen;
  if (c < 0x10000) *pp++ = c; else
    {
    c -= 0x10000;
    *pp++ = 0xd800 | (c >> 10);
    *pp++ = 0xdc00 | (c & 0x3ff);
    }
  }

*pp = 0;
*lenptr = pp - pbuffer16;
return 0;
}
#endif /* PCRE2_CODE_UNIT_WIDTH == 16 */



#if PCRE2_CODE_UNIT_WIDTH == 32
/*************************************************
*           Convert string to 32-bit             *
*************************************************/

/* In UTF mode the input is always interpreted as a string of UTF-8 bytes using
the original UTF-8 definition of RFC 2279, which allows for up to 6 bytes, and
code values from 0 to 0x7fffffff. However, values greater than the later UTF
limit of 0x10ffff cause an error.

In non-UTF mode the input is interpreted as UTF-8 if the utf8_input modifier
is set, and no limit is imposed. There is special interpretation of the 0xff
byte (which is illegal in UTF-8) in this case: it causes the top bit of the
next character to be set. This provides a way of generating 32-bit characters
greater than 0x7fffffff.

If all the input bytes are ASCII, the space needed for a 32-bit string is
exactly four times the 8-bit size. Otherwise, the size needed for a 32-bit
string is no more than four times, because the number of characters must be
less than the number of bytes. The result is always left in pbuffer32. Impose a
minimum size to save repeated re-sizing.

Note that this function does not object to surrogate values. This is
deliberate; it makes it possible to construct UTF-32 strings that are invalid,
for the purpose of testing that they are correctly faulted.

Arguments:
  p          points to a byte string
  utf        true in UTF mode
  lenptr     points to number of bytes in the string (excluding trailing zero)

Returns:     0 on success, with the length updated to the number of 32-bit
               data items used (excluding the trailing zero)
             OR -1 if a UTF-8 string is malformed
             OR -2 if a value > 0x10ffff is encountered in UTF mode
*/

static int
to32(uint8_t *p, int utf, PCRE2_SIZE *lenptr)
{
uint32_t *pp;
PCRE2_SIZE len = *lenptr;

if (pbuffer32_size < 4*len + 4)
  {
  if (pbuffer32 != NULL) free(pbuffer32);
  pbuffer32_size = 4*len + 4;
  if (pbuffer32_size < 8192) pbuffer32_size = 8192;
  pbuffer32 = (uint32_t *)malloc(pbuffer32_size);
  if (pbuffer32 == NULL)
    {
    fprintf(stderr, "pcre2test: malloc(%" SIZ_FORM ") failed for pbuffer32\n",
      pbuffer32_size);
    exit(1);
    }
  }

pp = pbuffer32;
if (!utf && (pat_patctl.control & CTL_UTF8_INPUT) == 0)
  {
  for (; len > 0; len--) *pp++ = *p++;
  }

else while (len > 0)
  {
  int chlen;
  uint32_t c;
  uint32_t topbit = 0;
  const uint8_t *end = p + len;
  if (!utf && *p == 0xff && len > 1)
    {
    topbit = 0x80000000u;
    p++;
    len--;
    }
  chlen = utf8_to_ord(p, end, &c);
  if (chlen <= 0) return -1;
  if (utf && c > 0x10ffff) return -2;
  p += chlen;
  len -= chlen;
  *pp++ = c | topbit;
  }

*pp = 0;
*lenptr = pp - pbuffer32;
return 0;
}
#endif /* PCRE2_CODE_UNIT_WIDTH == 32 */



/*************************************************
*        Check a modifer and find its field      *
*************************************************/

/* This function is called when a modifier has been identified. We check that
it is allowed here and find the field that is to be changed.

Arguments:
  m          the modifier list entry
  ctx        CTX_PAT     => pattern context
             CTX_POPPAT  => pattern context for popped pattern
             CTX_DEFPAT  => default pattern context
             CTX_DAT     => data context
             CTX_DEFDAT  => default data context
  pctl       point to pattern control block
  dctl       point to data control block
  c          a single character or 0

Returns:     a field pointer or NULL
*/

static void *
check_modifier(modstruct *m, int ctx, patctl *pctl, datctl *dctl, uint32_t c)
{
void *field = NULL;
PCRE2_SIZE offset = m->offset;

if (restrict_for_perl_test) switch(m->which)
  {
  case MOD_PNDP:
  case MOD_PATP:
  case MOD_DATP:
  case MOD_PDP:
  break;

  default:
  fprintf(outfile, "** \"%s\" is not allowed in a Perl-compatible test\n",
    m->name);
  return NULL;
  }

switch (m->which)
  {
  case MOD_CTC:  /* Compile context modifier */
  if (ctx == CTX_DEFPAT) field = contexts->default_pat_context;
    else if (ctx == CTX_PAT) field = contexts->pat_context;
  break;

  case MOD_CTM:  /* Match context modifier */
  if (ctx == CTX_DEFDAT) field = contexts->default_dat_context;
    else if (ctx == CTX_DAT) field = contexts->dat_context;
  break;

  case MOD_DAT:    /* Data line modifier */
  case MOD_DATP:   /* Allowed for Perl test */
  if (dctl != NULL) field = dctl;
  break;

  case MOD_PAT:    /* Pattern modifier */
  case MOD_PATP:   /* Allowed for Perl test */
  if (pctl != NULL) field = pctl;
  break;

  case MOD_PD:   /* Pattern or data line modifier */
  case MOD_PDP:  /* Ditto, allowed for Perl test */
  case MOD_PND:  /* Ditto, but not default pattern */
  case MOD_PNDP: /* Ditto, allowed for Perl test */
  if (dctl != NULL) field = dctl;
    else if (pctl != NULL && (m->which == MOD_PD || m->which == MOD_PDP ||
             ctx != CTX_DEFPAT))
      field = pctl;
  break;
  }

if (field == NULL)
  {
  if (c == 0)
    fprintf(outfile, "** \"%s\" is not valid here\n", m->name);
  else
    fprintf(outfile, "** /%c is not valid here\n", c);
  return NULL;
  }

return (char *)field + offset;
}



/*************************************************
*            Decode a modifier list              *
*************************************************/

/* A pointer to a control block is NULL when called in cases when that block is
not relevant. They are never all relevant in one call. At least one of patctl
and datctl is NULL. The second argument specifies which context to use for
modifiers that apply to contexts.

Arguments:
  p          point to modifier string
  ctx        CTX_PAT     => pattern context
             CTX_POPPAT  => pattern context for popped pattern
             CTX_DEFPAT  => default pattern context
             CTX_DAT     => data context
             CTX_DEFDAT  => default data context
  pctl       point to pattern control block
  dctl       point to data control block

Returns: TRUE if successful decode, FALSE otherwise
*/

static BOOL
decode_modifiers(uint8_t *p, int ctx, patctl *pctl, datctl *dctl)
{
uint8_t *ep, *pp;
long li;
unsigned long uli;
BOOL first = TRUE;

for (;;)
  {
  void *field;
  modstruct *m;
  BOOL off = FALSE;
  unsigned int i;
  size_t len;
  int index;
  char *endptr;

  /* Skip white space and commas. */

  while (isspace(*p) || *p == ',') p++;
  if (*p == 0) break;

  /* Find the end of the item; lose trailing whitespace at end of line. */

  for (ep = p; *ep != 0 && *ep != ','; ep++);
  if (*ep == 0)
    {
    while (ep > p && isspace(ep[-1])) ep--;
    *ep = 0;
    }

  /* Remember if the first character is '-'. */

  if (*p == '-')
    {
    off = TRUE;
    p++;
    }

  /* Find the length of a full-length modifier name, and scan for it. */

  pp = p;
  while (pp < ep && *pp != '=') pp++;
  index = scan_modifiers(p, pp - p);

  /* If the first modifier is unrecognized, try to interpret it as a sequence
  of single-character abbreviated modifiers. None of these modifiers have any
  associated data. They just set options or control bits. */

  if (index < 0)
    {
    uint32_t cc;
    uint8_t *mp = p;

    if (!first)
      {
      fprintf(outfile, "** Unrecognized modifier \"%.*s\"\n", (int)(ep-p), p);
      if (ep - p == 1)
        fprintf(outfile, "** Single-character modifiers must come first\n");
      return FALSE;
      }

    first = FALSE;

    for (cc = *p; cc != ',' && cc != '\n' && cc != 0; cc = *(++p))
      {
      for (i = 0; i < C1MODLISTCOUNT; i++)
        if (cc == c1modlist[i].onechar) break;

      if (i >= C1MODLISTCOUNT)
        {
        fprintf(outfile, "** Unrecognized modifier '%c' in modifier string "
          "\"%.*s\"\n", *p, (int)(ep-mp), mp);
        return FALSE;
        }

      if (c1modlist[i].index >= 0)
        {
        index = c1modlist[i].index;
        }

      else
        {
        index = scan_modifiers((const uint8_t *)(c1modlist[i].fullname),
          strlen(c1modlist[i].fullname));
        if (index < 0)
          {
          fprintf(outfile, "** Internal error: single-character equivalent "
            "modifier \"%s\" not found\n", c1modlist[i].fullname);
          return FALSE;
          }
        c1modlist[i].index = index;     /* Cache for next time */
        }

      field = check_modifier(modlist + index, ctx, pctl, dctl, contexts, *p);
      if (field == NULL) return FALSE;

      /* /x is a special case; a second appearance changes PCRE2_EXTENDED to
      PCRE2_EXTENDED_MORE. */

      if (cc == 'x' && (*((uint32_t *)field) & PCRE2_EXTENDED) != 0)
        {
        *((uint32_t *)field) &= ~PCRE2_EXTENDED;
        *((uint32_t *)field) |= PCRE2_EXTENDED_MORE;
        }
      else
        *((uint32_t *)field) |= modlist[index].value;
      }

    continue;    /* With tne next (fullname) modifier */
    }

  /* We have a match on a full-name modifier. Check for the existence of data
  when needed. */

  m = modlist + index;      /* Save typing */
  if (m->type != MOD_CTL && m->type != MOD_OPT && m->type != MOD_OPTMZ &&
      (m->type != MOD_IND || *pp == '='))
    {
    if (*pp++ != '=')
      {
      fprintf(outfile, "** '=' expected after \"%s\"\n", m->name);
      return FALSE;
      }
    if (off)
      {
      fprintf(outfile, "** '-' is not valid for \"%s\"\n", m->name);
      return FALSE;
      }
    }

  /* These on/off types have no data. */

  else if (*pp != ',' && *pp != '\n' && *pp != ' ' && *pp != 0)
    {
    fprintf(outfile, "** Unrecognized modifier '%.*s'\n", (int)(ep-p), p);
    return FALSE;
    }

  /* Set the data length for those types that have data. Then find the field
  that is to be set. If check_modifier() returns NULL, it has already output an
  error message. */

  len = ep - pp;
  field = check_modifier(m, ctx, pctl, dctl, contexts, *p);
  if (field == NULL) return FALSE;

  /* Process according to data type. */

  switch (m->type)
    {
    case MOD_CTL:
    case MOD_OPT:
    if (off) *((uint32_t *)field) &= ~m->value;
      else *((uint32_t *)field) |= m->value;
    break;

    case MOD_OPTMZ:
    pcre2_set_optimize(field, m->value);
    break;

    case MOD_BSR:
    if (len == 7 && strncmpic(pp, (const uint8_t *)"default", 7) == 0)
      {
#ifdef BSR_ANYCRLF
      *((uint16_t *)field) = PCRE2_BSR_ANYCRLF;
#else
      *((uint16_t *)field) = PCRE2_BSR_UNICODE;
#endif
      if (ctx == CTX_PAT || ctx == CTX_DEFPAT) pctl->control2 &= ~CTL2_BSR_SET;
        else dctl->control2 &= ~CTL2_BSR_SET;
      }
    else
      {
      if (len == 7 && strncmpic(pp, (const uint8_t *)"anycrlf", 7) == 0)
        *((uint16_t *)field) = PCRE2_BSR_ANYCRLF;
      else if (len == 7 && strncmpic(pp, (const uint8_t *)"unicode", 7) == 0)
        *((uint16_t *)field) = PCRE2_BSR_UNICODE;
      else goto INVALID_VALUE;
      if (ctx == CTX_PAT || ctx == CTX_DEFPAT) pctl->control2 |= CTL2_BSR_SET;
        else dctl->control2 |= CTL2_BSR_SET;
      }
    pp = ep;
    break;

    case MOD_CHR:  /* A single character */
    *((uint32_t *)field) = *pp++;
    break;

    case MOD_CON:  /* A convert type/options list */
    for (;; pp++)
      {
      uint8_t *colon = (uint8_t *)strchr((const char *)pp, ':');
      len = ((colon != NULL && colon < ep)? colon:ep) - pp;
      for (i = 0; i < convertlistcount; i++)
        {
        if (strncmpic(pp, (const uint8_t *)convertlist[i].name, len) == 0)
          {
          if (*((uint32_t *)field) == CONVERT_UNSET)
            *((uint32_t *)field) = convertlist[i].option;
          else
            *((uint32_t *)field) |= convertlist[i].option;
          break;
          }
        }
      if (i >= convertlistcount) goto INVALID_VALUE;
      pp += len;
      if (*pp != ':') break;
      }
    break;

    case MOD_IN2:    /* One or two unsigned integers */
    if (!isdigit(*pp)) goto INVALID_VALUE;
    uli = strtoul((const char *)pp, &endptr, 10);
    if (U32OVERFLOW(uli)) goto INVALID_VALUE;
    ((uint32_t *)field)[0] = (uint32_t)uli;
    if (*endptr == ':')
      {
      uli = strtoul((const char *)endptr+1, &endptr, 10);
      if (U32OVERFLOW(uli)) goto INVALID_VALUE;
      ((uint32_t *)field)[1] = (uint32_t)uli;
      }
    else ((uint32_t *)field)[1] = 0;
    pp = (uint8_t *)endptr;
    break;

    /* PCRE2_SIZE_MAX is usually SIZE_MAX, which may be greater, equal to, or
    less than ULONG_MAX. So first test for overflowing the long int, and then
    test for overflowing PCRE2_SIZE_MAX if it is smaller than ULONG_MAX. */

    case MOD_SIZ:    /* PCRE2_SIZE value */
    if (!isdigit(*pp)) goto INVALID_VALUE;
    uli = strtoul((const char *)pp, &endptr, 10);
    if (uli == ULONG_MAX) goto INVALID_VALUE;
#if ULONG_MAX > PCRE2_SIZE_MAX
    if (uli > PCRE2_SIZE_MAX) goto INVALID_VALUE;
#endif
    *((PCRE2_SIZE *)field) = (PCRE2_SIZE)uli;
    pp = (uint8_t *)endptr;
    break;

    case MOD_IND:    /* Unsigned integer with default */
    if (len == 0)
      {
      *((uint32_t *)field) = (uint32_t)(m->value);
      break;
      }
    PCRE2_FALLTHROUGH /* Fall through */

    case MOD_INT:    /* Unsigned integer */
    if (!isdigit(*pp)) goto INVALID_VALUE;
    uli = strtoul((const char *)pp, &endptr, 10);
    if (U32OVERFLOW(uli)) goto INVALID_VALUE;
    *((uint32_t *)field) = (uint32_t)uli;
    pp = (uint8_t *)endptr;
    break;

    case MOD_INS:   /* Signed integer */
    if (!isdigit(*pp) && *pp != '-') goto INVALID_VALUE;
    li = strtol((const char *)pp, &endptr, 10);
    if (S32OVERFLOW(li)) goto INVALID_VALUE;
    *((int32_t *)field) = (int32_t)li;
    pp = (uint8_t *)endptr;
    break;

    case MOD_NL:
    for (i = 0; i < sizeof(newlines)/sizeof(char *); i++)
      if (len == strlen(newlines[i]) &&
        strncmpic(pp, (const uint8_t *)newlines[i], len) == 0) break;
    if (i >= sizeof(newlines)/sizeof(char *)) goto INVALID_VALUE;
    if (i == 0)
      {
      *((uint16_t *)field) = NEWLINE_DEFAULT;
      if (ctx == CTX_PAT || ctx == CTX_DEFPAT) pctl->control2 &= ~CTL2_NL_SET;
        else dctl->control2 &= ~CTL2_NL_SET;
      }
    else
      {
      *((uint16_t *)field) = i;
      if (ctx == CTX_PAT || ctx == CTX_DEFPAT) pctl->control2 |= CTL2_NL_SET;
        else dctl->control2 |= CTL2_NL_SET;
      }
    pp = ep;
    break;

    case MOD_NN:              /* Name or (signed) number; may be several */
    if (isdigit(*pp) || *pp == '-')
      {
      int ct = MAXCPYGET - 1;
      int32_t value;
      li = strtol((const char *)pp, &endptr, 10);
      if (S32OVERFLOW(li)) goto INVALID_VALUE;
      value = (int32_t)li;
      field = (char *)field - m->offset + m->value;      /* Adjust field ptr */
      if (value >= 0)                                    /* Add new number */
        {
        while (*((int32_t *)field) >= 0 && ct-- > 0)   /* Skip previous */
          field = (char *)field + sizeof(int32_t);
        if (ct <= 0)
          {
          fprintf(outfile, "** Too many numeric \"%s\" modifiers\n", m->name);
          return FALSE;
          }
        }
      *((int32_t *)field) = value;
      if (ct > 0) ((int32_t *)field)[1] = -1;
      pp = (uint8_t *)endptr;
      }

    /* Multiple strings are put end to end. */

    else
      {
      char *nn = (char *)field;
      if (len > 0)                    /* Add new name */
        {
        if (len > MAX_NAME_SIZE)
          {
          fprintf(outfile, "** Group name in \"%s\" is too long\n", m->name);
          return FALSE;
          }
        while (*nn != 0) nn += strlen(nn) + 1;
        if (nn + len + 2 - (char *)field > LENCPYGET)
          {
          fprintf(outfile, "** Too many characters in named \"%s\" modifiers\n",
            m->name);
          return FALSE;
          }
        memcpy(nn, pp, len);
        }
      nn[len] = 0 ;
      nn[len+1] = 0;
      pp = ep;
      }
    break;

    case MOD_STR:
    if (len + 1 > m->value)
      {
      fprintf(outfile, "** Overlong value for \"%s\" (max %d code units)\n",
        m->name, m->value - 1);
      return FALSE;
      }
    memcpy(field, pp, len);
    ((uint8_t *)field)[len] = 0;
    pp = ep;
    break;
    }

  if (*pp != ',' && *pp != '\n' && *pp != ' ' && *pp != 0)
    {
    fprintf(outfile, "** Comma expected after modifier item \"%s\"\n", m->name);
    return FALSE;
    }

  p = pp;

  if (ctx == CTX_POPPAT &&
     (pctl->options != 0 ||
      pctl->tables_id != 0 ||
      pctl->locale[0] != 0 ||
      (pctl->control & NOTPOP_CONTROLS) != 0))
    {
    fprintf(outfile, "** \"%s\" is not valid here\n", m->name);
    return FALSE;
    }
  }

return TRUE;

INVALID_VALUE:
fprintf(outfile, "** Invalid value in \"%.*s\"\n", (int)(ep-p), p);
return FALSE;
}



/*************************************************
*             Get info from a pattern            *
*************************************************/

/* A wrapped call to pcre2_pattern_info(), applied to the current compiled
pattern.

Arguments:
  what        code for the required information
  where       where to put the answer
  unsetok     PCRE2_ERROR_UNSET is an "expected" result

Returns:      the return from pcre2_pattern_info()
*/

static int
pattern_info(int what, void *where, BOOL unsetok)
{
int rc;
PCRE2_PATTERN_INFO(rc, compiled_code, what, NULL);  /* Exercise the code */
PCRE2_PATTERN_INFO(rc, compiled_code, what, where);
if (rc >= 0) return 0;
if (rc != PCRE2_ERROR_UNSET || !unsetok)
  {
  fprintf(outfile, "Error %d from pcre2_pattern_info_%d(%d)\n", rc, test_mode,
    what);
  if (rc == PCRE2_ERROR_BADMODE)
    fprintf(outfile, "Running in %d-bit mode but pattern was compiled in "
      "%d-bit mode\n", test_mode,
      8 * (FLD(compiled_code, flags) & PCRE2_MODE_MASK));
  }
return rc;
}



/*************************************************
*      Show memory usage info for a pattern      *
*************************************************/

static void
show_memory_info(void)
{
uint32_t name_count, name_entry_size;
PCRE2_SIZE size, cblock_size, data_size;

/* One of the test_mode values will always be true, but to stop a compiler
warning we must initialize cblock_size. */

cblock_size = 0;
#ifdef SUPPORT_PCRE2_8
if (test_mode == PCRE8_MODE) cblock_size = sizeof(pcre2_real_code_8);
#endif
#ifdef SUPPORT_PCRE2_16
if (test_mode == PCRE16_MODE) cblock_size = sizeof(pcre2_real_code_16);
#endif
#ifdef SUPPORT_PCRE2_32
if (test_mode == PCRE32_MODE) cblock_size = sizeof(pcre2_real_code_32);
#endif

(void)pattern_info(PCRE2_INFO_SIZE, &size, FALSE);
(void)pattern_info(PCRE2_INFO_NAMECOUNT, &name_count, FALSE);
(void)pattern_info(PCRE2_INFO_NAMEENTRYSIZE, &name_entry_size, FALSE);

/* The uint32_t variables are cast before multiplying to avoid potential
 integer overflow. */
data_size = (PCRE2_SIZE)name_count * (PCRE2_SIZE)name_entry_size * (PCRE2_SIZE)code_unit_size;

fprintf(outfile, "Memory allocation - code size : %" SIZ_FORM "\n", size -
  cblock_size - data_size);
if (data_size != 0)
  fprintf(outfile, "Memory allocation - data size : %" SIZ_FORM "\n", data_size);

if (pat_patctl.jit != 0)
  {
  (void)pattern_info(PCRE2_INFO_JITSIZE, &size, FALSE);
  fprintf(outfile, "Memory allocation - JIT code  : %" SIZ_FORM "\n", size);
  }
}



/*************************************************
*       Show frame size info for a pattern       *
*************************************************/

static void
show_framesize(void)
{
PCRE2_SIZE frame_size;
(void)pattern_info(PCRE2_INFO_FRAMESIZE, &frame_size, FALSE);
fprintf(outfile, "Frame size for pcre2_match(): %" SIZ_FORM "\n", frame_size);
}



/*************************************************
*   Show heapframes size info for a match_data   *
*************************************************/

static void
show_heapframes_size(void)
{
PCRE2_SIZE heapframes_size;
PCRE2_GET_MATCH_DATA_HEAPFRAMES_SIZE(heapframes_size, match_data);
fprintf(outfile, "Heapframes size in match_data: %" SIZ_FORM "\n",
  heapframes_size);
}



/*************************************************
*         Get and output an error message        *
*************************************************/

static BOOL
print_error_message_file(FILE *file, int errorcode, const char *before,
  const char *after, BOOL badcode_ok)
{
int len;
PCRE2_GET_ERROR_MESSAGE(len, errorcode);
if (len == PCRE2_ERROR_BADDATA && badcode_ok)
  {
  fprintf(file, "%sPCRE2_ERROR_BADDATA (unknown error number)%s", before,
    after);
  }
else if (len < 0)
  {
  fprintf(file, "\n** pcre2test internal error: cannot interpret error "
    "number\n** Unexpected return (%d) from pcre2_get_error_message()\n", len);
  }
else
  {
  fprintf(file, "%s", before);
  PCHARSV(errorbuffer, 0, len, FALSE, file);
  fprintf(file, "%s", after);
  }
return len >= 0;
}

static BOOL
print_error_message(int errorcode, const char *before, const char *after)
{
return print_error_message_file(outfile, errorcode, before, after, FALSE);
}


/*************************************************
*     Callback function for callout enumeration  *
*************************************************/

/* Testing function to log data inside callout enumeration callbacks.

Argument:
  cb            pointer to enumerate block
  callout_data  user data

Returns:    0
*/

// XXX rename to something simpler...

static int callout_callback(pcre2_callout_enumerate_block_8 *cb,
  void *callout_data)
{
uint32_t i;
void *pattern_string = CASTVAR(void *, pbuffer);
BOOL utf = (FLD(compiled_code, overall_options) & PCRE2_UTF) != 0;
PCRE2_SIZE next_item_length = cb->next_item_length;

(void)callout_data;  /* Not currently displayed */

fprintf(outfile, "Callout ");
if (cb->callout_string != NULL)
  {
  uint32_t delimiter = CODE_UNIT(cb->callout_string, -1);
  fprintf(outfile, "%c", CHAR_OUTPUT(delimiter));
  PCHARSV(cb->callout_string, 0,
    cb->callout_string_length, utf, outfile);
  for (i = 0; callout_start_delims[i] != 0; i++)
    if (delimiter == callout_start_delims[i])
      {
      delimiter = callout_end_delims[i];
      break;
      }
  fprintf(outfile, "%c  ", CHAR_OUTPUT(delimiter));
  }
else fprintf(outfile, "%d  ", cb->callout_number);

if (next_item_length == 0 && CODE_UNIT(pattern_string, cb->pattern_position) != 0)
  next_item_length = 1;
PCHARSV(pattern_string, cb->pattern_position, next_item_length, utf, outfile);
fprintf(outfile, "\n");

return 0;
}



/*************************************************
*        Show information about a pattern        *
*************************************************/

/* This function is called after a pattern has been compiled if any of the
information-requesting controls have been set.

Arguments:  none

Returns:    PR_OK     continue processing next line
            PR_SKIP   skip to a blank line
            PR_ABEND  abort the pcre2test run
*/

static int
show_pattern_info(void)
{
uint32_t compile_options, overall_options, extra_options;
BOOL utf = (FLD(compiled_code, overall_options) & PCRE2_UTF) != 0;

if ((pat_patctl.control & (CTL_BINCODE|CTL_FULLBINCODE)) != 0)
  {
  fprintf(outfile, "------------------------------------------------------------------\n");
  PCRE2_PRINTINT((pat_patctl.control & CTL_FULLBINCODE) != 0);
  }

if ((pat_patctl.control & CTL_INFO) != 0)
  {
  int rc;
  void *nametable;
  uint8_t *start_bits;
  BOOL heap_limit_set, match_limit_set, depth_limit_set;
  uint32_t backrefmax, bsr_convention, capture_count, first_ctype, first_cunit,
    hasbackslashc, hascrorlf, jchanged, last_ctype, last_cunit, match_empty,
    depth_limit, heap_limit, match_limit, minlength, nameentrysize, namecount,
    newline_convention;

  /* Exercise the error route. */

  PCRE2_PATTERN_INFO(rc, compiled_code, 999, NULL);
  (void)rc;

  /* These info requests may return PCRE2_ERROR_UNSET. */

  switch(pattern_info(PCRE2_INFO_HEAPLIMIT, &heap_limit, TRUE))
    {
    case 0:
    heap_limit_set = TRUE;
    break;

    case PCRE2_ERROR_UNSET:
    heap_limit_set = FALSE;
    break;

    default:
    return PR_ABEND;
    }

  switch(pattern_info(PCRE2_INFO_MATCHLIMIT, &match_limit, TRUE))
    {
    case 0:
    match_limit_set = TRUE;
    break;

    case PCRE2_ERROR_UNSET:
    match_limit_set = FALSE;
    break;

    default:
    return PR_ABEND;
    }

  switch(pattern_info(PCRE2_INFO_DEPTHLIMIT, &depth_limit, TRUE))
    {
    case 0:
    depth_limit_set = TRUE;
    break;

    case PCRE2_ERROR_UNSET:
    depth_limit_set = FALSE;
    break;

    default:
    return PR_ABEND;
    }

  /* These info requests should always succeed. */

  if (pattern_info(PCRE2_INFO_BACKREFMAX, &backrefmax, FALSE) +
      pattern_info(PCRE2_INFO_BSR, &bsr_convention, FALSE) +
      pattern_info(PCRE2_INFO_CAPTURECOUNT, &capture_count, FALSE) +
      pattern_info(PCRE2_INFO_FIRSTBITMAP, &start_bits, FALSE) +
      pattern_info(PCRE2_INFO_FIRSTCODEUNIT, &first_cunit, FALSE) +
      pattern_info(PCRE2_INFO_FIRSTCODETYPE, &first_ctype, FALSE) +
      pattern_info(PCRE2_INFO_HASBACKSLASHC, &hasbackslashc, FALSE) +
      pattern_info(PCRE2_INFO_HASCRORLF, &hascrorlf, FALSE) +
      pattern_info(PCRE2_INFO_JCHANGED, &jchanged, FALSE) +
      pattern_info(PCRE2_INFO_LASTCODEUNIT, &last_cunit, FALSE) +
      pattern_info(PCRE2_INFO_LASTCODETYPE, &last_ctype, FALSE) +
      pattern_info(PCRE2_INFO_MATCHEMPTY, &match_empty, FALSE) +
      pattern_info(PCRE2_INFO_MINLENGTH, &minlength, FALSE) +
      pattern_info(PCRE2_INFO_NAMECOUNT, &namecount, FALSE) +
      pattern_info(PCRE2_INFO_NAMEENTRYSIZE, &nameentrysize, FALSE) +
      pattern_info(PCRE2_INFO_NAMETABLE, &nametable, FALSE) +
      pattern_info(PCRE2_INFO_NEWLINE, &newline_convention, FALSE)
      != 0)
    return PR_ABEND;

  fprintf(outfile, "Capture group count = %d\n", capture_count);

  if (backrefmax > 0)
    fprintf(outfile, "Max back reference = %d\n", backrefmax);

  if (maxlookbehind > 0)
    fprintf(outfile, "Max lookbehind = %d\n", maxlookbehind);

  if (heap_limit_set)
    fprintf(outfile, "Heap limit = %u\n", heap_limit);

  if (match_limit_set)
    fprintf(outfile, "Match limit = %u\n", match_limit);

  if (depth_limit_set)
    fprintf(outfile, "Depth limit = %u\n", depth_limit);

  if (namecount > 0)
    {
    fprintf(outfile, "Named capture groups:\n");
    for (; namecount > 0; namecount--)
      {
      int imm2_size = test_mode == PCRE8_MODE ? 2 : 1;
      size_t length = STRLEN(nametable + imm2_size);
      fprintf(outfile, "  ");

      /* In UTF mode the name may be a UTF string containing non-ASCII
      letters and digits. We must output it as a UTF-8 string. In non-UTF mode,
      use the normal string printing functions, which use escapes for all
      non-ASCII characters. */

      if (utf)
        {
#ifdef SUPPORT_PCRE2_32
        if (test_mode == PCRE32_MODE)
          {
          PCRE2_SPTR32 nameptr = (PCRE2_SPTR32)nametable + imm2_size;
          while (*nameptr != 0)
            {
            uint8_t u8buff[6];
            int len = ord_to_utf8(*nameptr++, u8buff);
            fprintf(outfile, "%.*s", len, u8buff);
            }
          }
#endif
#ifdef SUPPORT_PCRE2_16
        if (test_mode == PCRE16_MODE)
          {
          PCRE2_SPTR16 nameptr = (PCRE2_SPTR16)nametable + imm2_size;
          PCRE2_SPTR16 nameptr_end = nameptr + strlen16(nameptr);
          while (*nameptr != 0)
            {
            int len;
            uint8_t u8buff[6];
            uint32_t c;
            int ord_rc = utf16_to_ord(nameptr, nameptr_end, &c);
            if (ord_rc > 0) nameptr += ord_rc;
            else c = *nameptr++;
            len = ord_to_utf8(c, u8buff);
            fprintf(outfile, "%.*s", len, u8buff);
            }
          }
#endif
#ifdef SUPPORT_PCRE2_8
        if (test_mode == PCRE8_MODE)
          fprintf(outfile, "%s", (PCRE2_SPTR8)nametable + imm2_size);
#endif
        }
      else  /* Not UTF mode */
        {
        PCHARSV(nametable, imm2_size, length, FALSE, outfile);
        }

      while (length++ < nameentrysize - imm2_size) putc(' ', outfile);

#ifdef SUPPORT_PCRE2_32
      if (test_mode == PCRE32_MODE)
        fprintf(outfile, "%3d\n", (int)(((PCRE2_SPTR32)nametable)[0]));
#endif
#ifdef SUPPORT_PCRE2_16
      if (test_mode == PCRE16_MODE)
        fprintf(outfile, "%3d\n", (int)(((PCRE2_SPTR16)nametable)[0]));
#endif
#ifdef SUPPORT_PCRE2_8
      if (test_mode == PCRE8_MODE)
        fprintf(outfile, "%3d\n", (int)(
        ((((PCRE2_SPTR8)nametable)[0]) << 8) | ((PCRE2_SPTR8)nametable)[1]));
#endif

      nametable = (void *)((PCRE2_UCHAR8 *)nametable + nameentrysize * code_unit_size);
      }
    }

  if (hascrorlf)     fprintf(outfile, "Contains explicit CR or LF match\n");
  if (hasbackslashc) fprintf(outfile, "Contains \\C\n");
  if (match_empty)   fprintf(outfile, "May match empty string\n");

  pattern_info(PCRE2_INFO_ARGOPTIONS, &compile_options, FALSE);
  pattern_info(PCRE2_INFO_ALLOPTIONS, &overall_options, FALSE);
  pattern_info(PCRE2_INFO_EXTRAOPTIONS, &extra_options, FALSE);

  /* Remove UTF/UCP if they were there only because of forbid_utf. This saves
  cluttering up the verification output of non-UTF test files. */

  if ((pat_patctl.options & PCRE2_NEVER_UTF) == 0)
    {
    compile_options &= ~PCRE2_NEVER_UTF;
    overall_options &= ~PCRE2_NEVER_UTF;
    }

  if ((pat_patctl.options & PCRE2_NEVER_UCP) == 0)
    {
    compile_options &= ~PCRE2_NEVER_UCP;
    overall_options &= ~PCRE2_NEVER_UCP;
    }

  if ((compile_options|overall_options) != 0)
    {
    if (compile_options == overall_options)
      show_compile_options(compile_options, "Options:", "\n");
    else
      {
      show_compile_options(compile_options, "Compile options:", "\n");
      show_compile_options(overall_options, "Overall options:", "\n");
      }
    }

  if (extra_options != 0)
    show_compile_extra_options(extra_options, "Extra options:", "\n");

  if (FLD(compiled_code, optimization_flags) != PCRE2_OPTIMIZATION_ALL)
    show_optimize_flags(FLD(compiled_code, optimization_flags), "Optimizations: ", "\n");

  if (jchanged) fprintf(outfile, "Duplicate name status changes\n");

  if ((pat_patctl.control2 & CTL2_BSR_SET) != 0 ||
      (FLD(compiled_code, flags) & PCRE2_BSR_SET) != 0)
    fprintf(outfile, "\\R matches %s\n", (bsr_convention == PCRE2_BSR_UNICODE)?
      "any Unicode newline" : "CR, LF, or CRLF");

  if ((FLD(compiled_code, flags) & PCRE2_NL_SET) != 0)
    {
    switch (newline_convention)
      {
      case PCRE2_NEWLINE_CR:
      fprintf(outfile, "Forced newline is CR\n");
      break;

      case PCRE2_NEWLINE_LF:
      fprintf(outfile, "Forced newline is LF\n");
      break;

      case PCRE2_NEWLINE_CRLF:
      fprintf(outfile, "Forced newline is CRLF\n");
      break;

      case PCRE2_NEWLINE_ANYCRLF:
      fprintf(outfile, "Forced newline is CR, LF, or CRLF\n");
      break;

      case PCRE2_NEWLINE_ANY:
      fprintf(outfile, "Forced newline is any Unicode newline\n");
      break;

      case PCRE2_NEWLINE_NUL:
      fprintf(outfile, "Forced newline is NUL\n");
      break;

      default:
      break;
      }
    }

  if (first_ctype == 2)
    {
    fprintf(outfile, "First code unit at start or follows newline\n");
    }
  else if (first_ctype == 1)
    {
    const char *caseless =
      ((FLD(compiled_code, flags) & PCRE2_FIRSTCASELESS) == 0)?
      "" : " (caseless)";
    if (first_cunit != 0xff && PRINTABLE(first_cunit))
      fprintf(outfile, "First code unit = \'%c\'%s\n", CHAR_OUTPUT(first_cunit),
              caseless);
    else
      {
      fprintf(outfile, "First code unit = ");
      if (first_cunit == 0xff)
        fprintf(outfile, "\\xff");
      else
        pchar(first_cunit, FALSE, outfile);
      fprintf(outfile, "%s\n", caseless);
      }
    }
  else if (start_bits != NULL)
    {
    int input;
    int c = 24;
    fprintf(outfile, "Starting code units:");
    for (input = 0; input < 256; input++)
      {
      int i = CHAR_INPUT_HEX(input);
      if ((start_bits[i/8] & (1u << (i&7))) != 0)
        {
        if (c > 75)
          {
          fprintf(outfile, "\n ");
          c = 2;
          }
        if (PRINTABLE(i) && i != CHAR_SPACE)
          {
          fprintf(outfile, " %c", CHAR_OUTPUT(i));
          c += 2;
          }
        else
          {
          fprintf(outfile, " \\x%02x", CHAR_OUTPUT_HEX(i));
          c += 5;
          }
        }
      }
    fprintf(outfile, "\n");
    }

  if (last_ctype != 0)
    {
    const char *caseless =
      ((FLD(compiled_code, flags) & PCRE2_LASTCASELESS) == 0)?
      "" : " (caseless)";
    if (PRINTABLE(last_cunit))
      fprintf(outfile, "Last code unit = \'%c\'%s\n", CHAR_OUTPUT(last_cunit),
              caseless);
    else
      {
      fprintf(outfile, "Last code unit = ");
      pchar(last_cunit, FALSE, outfile);
      fprintf(outfile, "%s\n", caseless);
      }
    }

  if ((FLD(compiled_code, optimization_flags) & PCRE2_OPTIM_START_OPTIMIZE) != 0)
    fprintf(outfile, "Subject length lower bound = %d\n", minlength);

  if (pat_patctl.jit != 0 && (pat_patctl.control & CTL_JITVERIFY) != 0)
    {
#ifdef SUPPORT_JIT
    if (FLD(compiled_code, executable_jit) != NULL)
      fprintf(outfile, "JIT compilation was successful\n");
    else
      {
      fprintf(outfile, "JIT compilation was not successful");
      if (jitrc != 0 && !print_error_message(jitrc, " (", ")"))
        return PR_ABEND;
      fprintf(outfile, "\n");
      }
#else
      fprintf(outfile, "JIT support is not available in this version of PCRE2\n");
#endif
    }
  }

if ((pat_patctl.control & CTL_CALLOUT_INFO) != 0)
  {
  int errorcode;
  PCRE2_CALLOUT_ENUMERATE(errorcode, callout_callback, 0);
  if (errorcode != 0)
    {
    fprintf(outfile, "Callout enumerate failed: error %d: ", errorcode);
    if (errorcode < 0 && !print_error_message(errorcode, "", "\n"))
      return PR_ABEND;
    return PR_SKIP;
    }
  }

return PR_OK;
}



/*************************************************
*              Handle serialization error        *
*************************************************/

/* Print an error message after a serialization failure.

Arguments:
  rc         the error code
  msg        an initial message for what failed

Returns:     FALSE if print_error_message() fails
*/

static BOOL
serial_error(int rc, const char *msg)
{
fprintf(outfile, "%s failed: error %d: ", msg, rc);
return print_error_message(rc, "", "\n");
}



/*************************************************
*               Process command line             *
*************************************************/

/* This function is called for lines beginning with # and a character that is
not ! or whitespace, when encountered between tests, which means that there is
no compiled pattern (compiled_code is NULL). The line is in buffer.

Arguments:  none

Returns:    PR_OK     continue processing next line
            PR_SKIP   skip to a blank line
            PR_ABEND  abort the pcre2test run
*/

static int
process_command(void)
{
FILE *f;
PCRE2_SIZE serial_size;
size_t i;
int rc, cmd, yield;
uint16_t first_listed_newline;
const char *cmdname;
size_t cmdlen;
uint8_t *argptr, *serial;
BOOL if_inverted;

yield = PR_OK;
cmd = CMD_UNKNOWN;
cmdlen = 0;

for (i = 0; i < cmdlistcount; i++)
  {
  cmdname = cmdlist[i].name;
  cmdlen = strlen(cmdname);
  if (strncmp((char *)(buffer+1), cmdname, cmdlen) == 0 &&
      (buffer[cmdlen+1] == 0 || isspace(buffer[cmdlen+1])))
    {
    cmd = cmdlist[i].value;
    break;
    }
  }

if (preprocess_only && cmd != CMD_IF && cmd != CMD_ENDIF)
  return PR_OK;

argptr = buffer + cmdlen + 1;

if (restrict_for_perl_test && cmd != CMD_PATTERN && cmd != CMD_SUBJECT &&
    cmd != CMD_IF && cmd != CMD_ENDIF)
  {
  fprintf(outfile, "** #%s is not allowed after #perltest\n", cmdname);
  return PR_ABEND;
  }

switch(cmd)
  {
  case CMD_UNKNOWN:
  fprintf(outfile, "** Unknown command: %s", buffer);
  break;

  case CMD_FORBID_UTF:
  forbid_utf = PCRE2_NEVER_UTF|PCRE2_NEVER_UCP;
  break;

  case CMD_PERLTEST:
  restrict_for_perl_test = TRUE;
  break;

  /* Set default pattern modifiers */

  case CMD_PATTERN:
  (void)decode_modifiers(argptr, CTX_DEFPAT, &def_patctl, NULL);
  if (def_patctl.jit == 0 && (def_patctl.control & CTL_JITVERIFY) != 0)
    def_patctl.jit = JIT_DEFAULT;
  break;

  /* Set default subject modifiers */

  case CMD_SUBJECT:
  (void)decode_modifiers(argptr, CTX_DEFDAT, NULL, &def_datctl);
  break;

  /* Check the default newline, and if not one of those listed, set up the
  first one to be forced. An empty list unsets. */

  case CMD_NEWLINE_DEFAULT:
  local_newline_default = 0;   /* Unset */
  first_listed_newline = 0;
  for (;;)
    {
    while (isspace(*argptr)) argptr++;
    if (*argptr == 0) break;
    for (uint16_t j = 1; j < sizeof(newlines)/sizeof(char *); j++)
      {
      size_t nlen = strlen(newlines[j]);
      if (strncmpic(argptr, (const uint8_t *)newlines[j], nlen) == 0 &&
          isspace(argptr[nlen]))
        {
        if (j == NEWLINE_DEFAULT) return PR_OK;  /* Default is valid */
        if (first_listed_newline == 0) first_listed_newline = j;
        }
      }
    while (*argptr != 0 && !isspace(*argptr)) argptr++;
    }
  local_newline_default = first_listed_newline;
  break;

  /* Pop or copy a compiled pattern off the stack. Modifiers that do not affect
  the compiled pattern (e.g. to give information) are permitted. The default
  pattern modifiers are ignored. */

  case CMD_POP:
  case CMD_POPCOPY:
  if (patstacknext <= 0)
    {
    fprintf(outfile, "** Can't pop off an empty stack\n");
    return PR_SKIP;
    }
  memset(&pat_patctl, 0, sizeof(patctl));   /* Completely unset */
  if (!decode_modifiers(argptr, CTX_POPPAT, &pat_patctl, NULL))
    return PR_SKIP;

  // XXX are we leaking anything here?
  if (cmd == CMD_POP)
    {
    SET(compiled_code, patstack[--patstacknext]);
    }
  else
    {
    PCRE2_CODE_COPY_FROM_VOID(compiled_code, patstack[patstacknext - 1]);
    }

  if (pat_patctl.jit != 0)
    {
    PCRE2_JIT_COMPILE(jitrc, compiled_code, pat_patctl.jit);
    }
  if ((pat_patctl.control & CTL_MEMORY) != 0) show_memory_info();
  if ((pat_patctl.control2 & CTL2_FRAMESIZE) != 0) show_framesize();
  if ((pat_patctl.control & CTL_ANYINFO) != 0)
    {
    rc = show_pattern_info();
    if (rc != PR_OK) return rc;
    }
  break;

  /* Save the stack of compiled patterns to a file, then empty the stack. */

  case CMD_SAVE:
  if (patstacknext <= 0)
    {
    fprintf(outfile, "** No stacked patterns to save\n");
    return PR_OK;
    }

  rc = open_file(argptr+1, BINARY_OUTPUT_MODE, &f, "#save");
  if (rc != PR_OK) return rc;

  PCRE2_SERIALIZE_ENCODE(rc, patstack, patstacknext, &serial, &serial_size,
    general_context);
  if (rc < 0)
    {
    fclose(f);
    if (!serial_error(rc, "Serialization")) return PR_ABEND;
    break;
    }

  /* Write the length at the start of the file to make it straightforward to
  get the right memory when re-loading. This saves having to read the file size
  in different operating systems. To allow for different endianness (even
  though reloading with the opposite endianness does not work), write the
  length byte-by-byte. */

  for (i = 0; i < 4; i++) fputc((serial_size >> (i*8)) & 255, f);
  if (fwrite(serial, 1, serial_size, f) != serial_size)
    {
    fprintf(outfile, "** Wrong return from fwrite()\n");
    fclose(f);
    return PR_ABEND;
    }

  fclose(f);
  PCRE2_SERIALIZE_FREE(serial);
  while(patstacknext > 0)
    {
    SET(compiled_code, patstack[--patstacknext]);
    SUB1(pcre2_code_free, compiled_code);
    }
  SET(compiled_code, NULL);
  break;

  /* Load a set of compiled patterns from a file onto the stack */

  case CMD_LOAD:
  rc = open_file(argptr+1, BINARY_INPUT_MODE, &f, "#load");
  if (rc != PR_OK) return rc;

  serial_size = 0;
  for (i = 0; i < 4; i++) serial_size |= fgetc(f) << (i*8);

  serial = malloc(serial_size);
  if (serial == NULL)
    {
    fprintf(outfile, "** Failed to get memory (size %" SIZ_FORM ") for #load\n",
      serial_size);
    fclose(f);
    return PR_ABEND;
    }

  i = fread(serial, 1, serial_size, f);
  fclose(f);

  if (i != serial_size)
    {
    fprintf(outfile, "** Wrong return from fread()\n");
    yield = PR_ABEND;
    }
  else
    {
    PCRE2_SERIALIZE_GET_NUMBER_OF_CODES(rc, serial);
    if (rc < 0)
      {
      if (!serial_error(rc, "Get number of codes")) yield = PR_ABEND;
      }
    else
      {
      if (rc + patstacknext > PATSTACKSIZE)
        {
        fprintf(outfile, "** Not enough space on pattern stack for %d pattern%s\n",
          rc, (rc == 1)? "" : "s");
        rc = PATSTACKSIZE - patstacknext;
        fprintf(outfile, "** Decoding %d pattern%s\n", rc,
          (rc == 1)? "" : "s");
        }
      PCRE2_SERIALIZE_DECODE(rc, patstack + patstacknext, rc, serial,
        general_context);
      if (rc < 0)
        {
        if (!serial_error(rc, "Deserialization")) yield = PR_ABEND;
        }
      else patstacknext += rc;
      }
    }

  free(serial);
  break;

  /* Load a set of binary tables into tables3. */

  case CMD_LOADTABLES:
  rc = open_file(argptr+1, BINARY_INPUT_MODE, &f, "#loadtables");
  if (rc != PR_OK) return rc;

  if (tables3 == NULL)
    {
    int r;
    PCRE2_CONFIG(r, PCRE2_CONFIG_TABLES_LENGTH, &loadtables_length);
    if (r >= 0) tables3 = malloc(loadtables_length);
    }

  if (tables3 == NULL)
    {
    fprintf(outfile, "** Failed: malloc/config for #loadtables\n");
    yield = PR_ABEND;
    }
  else if (fread(tables3, 1, loadtables_length, f) != loadtables_length)
    {
    fprintf(outfile, "** Wrong return from fread()\n");
    yield = PR_ABEND;
    }

  fclose(f);
  break;

  case CMD_IF:
  if (inside_if)
    {
    fprintf(outfile, "** Nested #if not supported\n");
    return PR_ABEND;
    }

  while (isspace(*argptr)) argptr++;
  if_inverted = FALSE;
  if (*argptr == '!')
    {
    argptr++;
    if_inverted = TRUE;
    }
  while (isspace(*argptr)) argptr++;
  for (i = 0; i < COPTLISTCOUNT; i++)
    {
    size_t optlen = strlen(coptlist[i].name);
    const uint8_t *argptr_trail;
    if (coptlist[i].type != CONF_FIX)
      continue;
    if (strncmp((const char*)argptr, coptlist[i].name, optlen) != 0)
      continue;
    argptr_trail = argptr + optlen;
    while (isspace(*argptr_trail)) argptr_trail++;
    if (*argptr_trail == 0 || *argptr_trail == '\n')
      break;
    }
  if (i == COPTLISTCOUNT)
    {
    fprintf(outfile, "** Unknown condition: %s\n", buffer);
    return PR_ABEND;
    }

  /* Condition FALSE - skip this line and everything until #endif. */
  if ((coptlist[i].value != 0) == if_inverted)
    yield = PR_ENDIF;

  inside_if = TRUE;
  break;

  case CMD_ENDIF:
  if (!inside_if)
    {
    fprintf(outfile, "** Unexpected #endif\n");
    return PR_ABEND;
    }
  inside_if = FALSE;
  break;
  }

return yield;
}



/*************************************************
*               Process pattern line             *
*************************************************/

/* This function is called when the input buffer contains the start of a
pattern. The first character is known to be a valid delimiter. The pattern is
read, modifiers are interpreted, and a suitable local context is set up for
this test. The pattern is then compiled.

Arguments:  none

Returns:    PR_OK     continue processing next line
            PR_SKIP   skip to a blank line
            PR_ABEND  abort the pcre2test run
*/

static int
process_pattern(void)
{
BOOL utf;
uint32_t k;
uint8_t *p = buffer;
unsigned int delimiter = *p++;
int errorcode;
void *use_pat_context;
void *use_pbuffer = NULL;
uint32_t use_forbid_utf = forbid_utf;
PCRE2_SIZE patlen;
PCRE2_SIZE valgrind_access_length;
PCRE2_SIZE erroroffset;

/* The perltest.sh script supports only / as a delimiter. */

if (restrict_for_perl_test && delimiter != '/')
  {
  fprintf(outfile, "** The only allowed delimiter after #perltest is '/'\n");
  return PR_ABEND;
  }

/* Initialize the context and pattern/data controls for this test from the
defaults. */

PATCTXCPY(pat_context, default_pat_context);
memcpy(&pat_patctl, &def_patctl, sizeof(patctl));

/* Find the end of the pattern, reading more lines if necessary. */

for(;;)
  {
  while (*p != 0)
    {
    if (*p == '\\' && p[1] != 0) p++;
      else if (*p == delimiter) break;
    p++;
    }
  if (*p != 0) break;
  if ((p = extend_inputline(infile, p, "    > ")) == NULL)
    {
    fprintf(outfile, "** Unexpected EOF\n");
    return PR_ABEND;
    }
  if (!INTERACTIVE(infile)) fprintf(outfile, "%s", (char *)p);
  }

/* If the first character after the delimiter is backslash, make the pattern
end with backslash. This is purely to provide a way of testing for the error
message when a pattern ends with backslash. */

if (p[1] == '\\') *p++ = '\\';

/* Terminate the pattern at the delimiter, and compute the length. */

*p++ = 0;
patlen = p - buffer - 2;

/* Look for modifiers and options after the final delimiter. */

if (!decode_modifiers(p, CTX_PAT, &pat_patctl, NULL)) return PR_SKIP;

/* Note that the match_invalid_utf option also sets utf when passed to
pcre2_compile(). */

utf = (pat_patctl.options & (PCRE2_UTF|PCRE2_MATCH_INVALID_UTF)) != 0;

/* The utf8_input modifier is not allowed in 8-bit mode, and is mutually
exclusive with the utf modifier. */

if ((pat_patctl.control & CTL_UTF8_INPUT) != 0)
  {
  if (test_mode == PCRE8_MODE)
    {
    fprintf(outfile, "** The utf8_input modifier is not allowed in 8-bit mode\n");
    return PR_SKIP;
    }
  if (utf)
    {
    fprintf(outfile, "** The utf and utf8_input modifiers are mutually exclusive\n");
    return PR_SKIP;
    }
  }

/* The convert and posix modifiers are mutually exclusive. */

if (pat_patctl.convert_type != CONVERT_UNSET &&
    (pat_patctl.control & CTL_POSIX) != 0)
  {
  fprintf(outfile, "** The convert and posix modifiers are mutually exclusive\n");
  return PR_SKIP;
  }

/* Check for mutually exclusive control modifiers. At present, these are all in
the first control word. */

for (k = 0; k < sizeof(exclusive_pat_controls)/sizeof(uint32_t); k++)
  {
  uint32_t c = pat_patctl.control & exclusive_pat_controls[k];
  if (c != 0 && c != (c & (~c+1)))
    {
    show_controls(c, 0, "** Not allowed together:");
    fprintf(outfile, "\n");
    return PR_SKIP;
    }
  }

/* Assume full JIT compile for jitverify and/or jitfast if nothing else was
specified. */

if (pat_patctl.jit == 0 &&
    (pat_patctl.control & (CTL_JITVERIFY|CTL_JITFAST)) != 0)
  pat_patctl.jit = JIT_DEFAULT;

/* Now copy the pattern to pbuffer8 for use in 8-bit testing. Convert from hex
if requested (literal strings in quotes may be present within the hexadecimal
pairs). The result must necessarily be fewer characters so will always fit in
pbuffer8. */

if ((pat_patctl.control & CTL_HEXPAT) != 0)
  {
  uint8_t *pp, *pt;
  uint32_t c, d;

  pt = pbuffer8;
  for (pp = buffer + 1; *pp != 0; pp++)
    {
    if (isspace(*pp)) continue;
    c = *pp++;

    /* Handle a literal substring */

    if (c == '\'' || c == '"')
      {
      uint8_t *pq = pp;
      for (;; pp++)
        {
        d = *pp;
        if (d == 0)
          {
          fprintf(outfile, "** Missing closing quote in hex pattern: "
            "opening quote is at offset %" PTR_FORM ".\n", pq - buffer - 2);
          return PR_SKIP;
          }
        if (d == c) break;
        *pt++ = d;
        }
      }

    /* Expect a hex pair */

    else
      {
      if (!isxdigit(c))
        {
        fprintf(outfile, "** Unexpected non-hex-digit '%c' at offset %"
          PTR_FORM " in hex pattern: quote missing?\n", c, pp - buffer - 2);
        return PR_SKIP;
        }
      if (*pp == 0)
        {
        fprintf(outfile, "** Odd number of digits in hex pattern\n");
        return PR_SKIP;
        }
      d = *pp;
      if (!isxdigit(d))
        {
        fprintf(outfile, "** Unexpected non-hex-digit '%c' at offset %"
          PTR_FORM " in hex pattern: quote missing?\n", d, pp - buffer - 1);
        return PR_SKIP;
        }
      c = toupper(c);
      d = toupper(d);
      c = isdigit(c)? (c - '0') : (c - 'A' + 10);
      d = isdigit(d)? (d - '0') : (d - 'A' + 10);
      *pt++ = CHAR_OUTPUT(CHAR_INPUT_HEX((c << 4) + d));
      }
    }
  *pt = 0;
  patlen = pt - pbuffer8;
  }

/* If not a hex string, process for repetition expansion if requested. */

else if ((pat_patctl.control & CTL_EXPAND) != 0)
  {
  uint8_t *pp, *pt;

  pt = pbuffer8;
  for (pp = buffer + 1; *pp != 0; pp++)
    {
    uint8_t *pc = pp;
    uint32_t count = 1;
    size_t length = 1;

    /* Check for replication syntax; if not found, the defaults just set will
    prevail and one character will be copied. */

    if (pp[0] == '\\' && pp[1] == '[')
      {
      uint8_t *pe;
      for (pe = pp + 2; *pe != 0; pe++)
        {
        if (pe[0] == ']' && pe[1] == '{')
          {
          size_t clen = pe - pc - 2;
          uint32_t i = 0;
          unsigned long uli;
          char *endptr;

          pe += 2;
          uli = strtoul((const char *)pe, &endptr, 10);
          if (U32OVERFLOW(uli))
            {
            fprintf(outfile, "** Pattern repeat count too large\n");
            return PR_SKIP;
            }

          i = (uint32_t)uli;
          pe = (uint8_t *)endptr;
          if (*pe == '}')
            {
            if (i == 0)
              {
              fprintf(outfile, "** Zero repeat not allowed\n");
              return PR_SKIP;
              }
            pc += 2;
            count = i;
            length = clen;
            pp = pe;
            break;
            }
          }
        }
      }

    /* Add to output. If the buffer is too small expand it. The function for
    expanding buffers always keeps buffer and pbuffer8 in step as far as their
    size goes. */

    while (pt + count * length > pbuffer8 + pbuffer8_size)
      {
      size_t pc_offset = pc - buffer;
      size_t pp_offset = pp - buffer;
      size_t pt_offset = pt - pbuffer8;
      expand_input_buffers();
      pc = buffer + pc_offset;
      pp = buffer + pp_offset;
      pt = pbuffer8 + pt_offset;
      }

    for (; count > 0; count--)
      {
      memcpy(pt, pc, length);
      pt += length;
      }
    }

  *pt = 0;
  patlen = pt - pbuffer8;

  if ((pat_patctl.control & CTL_INFO) != 0)
    fprintf(outfile, "Expanded: %s\n", pbuffer8);
  }

/* Neither hex nor expanded, just copy the input verbatim. */

else
  {
  strncpy((char *)pbuffer8, (char *)(buffer+1), patlen + 1);
  }

/* Sort out character tables */

if (pat_patctl.locale[0] != 0)
  {
  if (pat_patctl.tables_id != 0)
    {
    fprintf(outfile, "** 'Locale' and 'tables' must not both be set\n");
    return PR_SKIP;
    }
  if (setlocale(LC_CTYPE, (const char *)pat_patctl.locale) == NULL)
    {
    fprintf(outfile, "** Failed to set locale \"%s\"\n", pat_patctl.locale);
    return PR_SKIP;
    }
  if (strcmp((const char *)pat_patctl.locale, (const char *)locale_name) != 0)
    {
    snprintf((char *)locale_name, sizeof(locale_name), "%s", (char *)pat_patctl.locale);
    if (locale_tables != NULL)
      {
      PCRE2_MAKETABLES_FREE(general_context, (const void *)locale_tables);
      }
    PCRE2_MAKETABLES(locale_tables, general_context);
    }
  use_tables = locale_tables;
  }

else switch (pat_patctl.tables_id)
  {
  case 0: use_tables = NULL; break;
  case 1: use_tables = tables1; break;
  case 2: use_tables = tables2; break;

  case 3:
  if (tables3 == NULL)
    {
    fprintf(outfile, "** 'Tables = 3' is invalid: binary tables have not "
      "been loaded\n");
    return PR_SKIP;
    }
  use_tables = tables3;
  break;

  default:
  fprintf(outfile, "** 'Tables' must specify 0, 1, 2, or 3.\n");
  return PR_SKIP;
  }

PCRE2_SET_CHARACTER_TABLES(pat_context, use_tables);

/* Set up for the stackguard test. */

if (pat_patctl.stackguard_test != 0)
  {
  PCRE2_SET_COMPILE_RECURSION_GUARD(pat_context, stack_guard, NULL);
  }

/* Handle compiling via the POSIX interface, which doesn't support the
timing, showing, or debugging options, nor the ability to pass over
local character tables. Neither does it have 16-bit or 32-bit support. */

if ((pat_patctl.control & CTL_POSIX) != 0)
  {
#ifdef SUPPORT_PCRE2_8
  int rc;
  int cflags = 0;
  const char *msg = "** Ignored with POSIX interface:";
#endif

  if (test_mode != PCRE8_MODE)
    {
    fprintf(outfile, "** The POSIX interface is available only in 8-bit mode\n");
    return PR_SKIP;
    }

#ifdef SUPPORT_PCRE2_8
  /* Check for features that the POSIX interface does not support. */

  if (pat_patctl.locale[0] != 0) prmsg(&msg, "locale");
  if (pat_patctl.replacement[0] != 0) prmsg(&msg, "replace");
  if (pat_patctl.tables_id != 0) prmsg(&msg, "tables");
  if (pat_patctl.stackguard_test != 0) prmsg(&msg, "stackguard");
  if (timeit > 0) prmsg(&msg, "timing");
  if (pat_patctl.jit != 0) prmsg(&msg, "JIT");

  if ((pat_patctl.options & ~POSIX_SUPPORTED_COMPILE_OPTIONS) != 0)
    {
    show_compile_options(
      pat_patctl.options & (uint32_t)(~POSIX_SUPPORTED_COMPILE_OPTIONS),
        msg, "");
    msg = "";
    }

  if ((FLD(pat_context, extra_options) &
       (uint32_t)(~POSIX_SUPPORTED_COMPILE_EXTRA_OPTIONS)) != 0)
    {
    show_compile_extra_options(
      FLD(pat_context, extra_options) &
        (uint32_t)(~POSIX_SUPPORTED_COMPILE_EXTRA_OPTIONS), msg, "");
    msg = "";
    }

  if ((pat_patctl.control & (uint32_t)(~POSIX_SUPPORTED_COMPILE_CONTROLS)) != 0 ||
      (pat_patctl.control2 & (uint32_t)(~POSIX_SUPPORTED_COMPILE_CONTROLS2)) != 0)
    {
    show_controls(
      pat_patctl.control & (uint32_t)(~POSIX_SUPPORTED_COMPILE_CONTROLS),
      pat_patctl.control2 & (uint32_t)(~POSIX_SUPPORTED_COMPILE_CONTROLS2),
      msg);
    msg = "";

    /* Remove ignored options so as not to get a repeated message for those
    that are actually subject controls. */

    pat_patctl.control &= (uint32_t)(POSIX_SUPPORTED_COMPILE_CONTROLS);
    pat_patctl.control2 &= (uint32_t)(POSIX_SUPPORTED_COMPILE_CONTROLS2);
    }

  if (local_newline_default != 0) prmsg(&msg, "#newline_default");
  if (FLD(pat_context, max_pattern_length) != PCRE2_UNSET)
    prmsg(&msg, "max_pattern_length");
  if (FLD(pat_context, max_pattern_compiled_length) != PCRE2_UNSET)
    prmsg(&msg, "max_pattern_compiled_length");
  if (FLD(pat_context, parens_nest_limit) != PARENS_NEST_DEFAULT)
    prmsg(&msg, "parens_nest_limit");

  if (msg[0] == 0) fprintf(outfile, "\n");

  /* Translate PCRE2 options to POSIX options and then compile. */

  if (utf) cflags |= REG_UTF;
  if ((pat_patctl.control & CTL_POSIX_NOSUB) != 0) cflags |= REG_NOSUB;
  if ((pat_patctl.options & PCRE2_UCP) != 0) cflags |= REG_UCP;
  if ((pat_patctl.options & PCRE2_CASELESS) != 0) cflags |= REG_ICASE;
  if ((pat_patctl.options & PCRE2_LITERAL) != 0) cflags |= REG_NOSPEC;
  if ((pat_patctl.options & PCRE2_MULTILINE) != 0) cflags |= REG_NEWLINE;
  if ((pat_patctl.options & PCRE2_DOTALL) != 0) cflags |= REG_DOTALL;
  if ((pat_patctl.options & PCRE2_UNGREEDY) != 0) cflags |= REG_UNGREEDY;

  if ((pat_patctl.control & (CTL_HEXPAT|CTL_USE_LENGTH)) != 0)
    {
    preg.re_endp = (char *)pbuffer8 + patlen;
    cflags |= REG_PEND;
    }

#if defined(EBCDIC) && !EBCDIC_IO
  ascii_to_ebcdic_str(pbuffer8, patlen);
#endif

  rc = regcomp(&preg, (char *)pbuffer8, cflags);

  /* Compiling failed */

  if (rc != 0)
    {
    size_t bsize, usize;
    int psize;

    preg.re_pcre2_code = NULL;     /* In case something was left in there */
    preg.re_match_data = NULL;

    bsize = (pat_patctl.regerror_buffsize != 0)?
      pat_patctl.regerror_buffsize : pbuffer8_size;
    if (bsize + 8 < pbuffer8_size)
      memcpy(pbuffer8 + bsize, "DEADBEEF", 8);
    usize = regerror(rc, &preg, (char *)pbuffer8, bsize);

    /* Inside regerror(), snprintf() is used. If the buffer is too small, some
    versions of snprintf() put a zero byte at the end, but others do not.
    Therefore, we print a maximum of one less than the size of the buffer. */

    psize = (int)bsize - 1;
    fprintf(outfile, "Failed: POSIX code %d: %.*s\n", rc, psize, pbuffer8);
    if (usize > bsize)
      {
      fprintf(outfile, "** regerror() message truncated\n");
      if (memcmp(pbuffer8 + bsize, "DEADBEEF", 8) != 0)
        fprintf(outfile, "** regerror() buffer overflow\n");
      }
    return PR_SKIP;
    }

  /* Compiling succeeded. Check that the values in the preg block are sensible.
  It can happen that pcre2test is accidentally linked with a different POSIX
  library which succeeds, but of course puts different things into preg. In
  this situation, calling regfree() may cause a segfault (or invalid free() in
  valgrind), so ensure that preg.re_pcre2_code is NULL, which suppresses the
  calling of regfree() on exit. */

  if (preg.re_pcre2_code == NULL ||
      ((pcre2_real_code_8 *)preg.re_pcre2_code)->magic_number != MAGIC_NUMBER ||
      ((pcre2_real_code_8 *)preg.re_pcre2_code)->top_bracket != preg.re_nsub ||
      preg.re_match_data == NULL ||
      preg.re_cflags != cflags)
    {
    fprintf(outfile,
      "** The regcomp() function returned zero (success), but the values set\n"
      "** in the preg block are not valid for PCRE2. Check that pcre2test is\n"
      "** linked with PCRE2's pcre2posix module (-lpcre2-posix) and not with\n"
      "** some other POSIX regex library.\n**\n");
    preg.re_pcre2_code = NULL;
    return PR_ABEND;
    }

  return PR_OK;
#endif  /* SUPPORT_PCRE2_8 */
  }

/* Handle compiling via the native interface. Controls that act later are
ignored with "push". Replacements are locked out. */

if ((pat_patctl.control & (CTL_PUSH|CTL_PUSHCOPY|CTL_PUSHTABLESCOPY)) != 0)
  {
  if (pat_patctl.replacement[0] != 0)
    {
    fprintf(outfile, "** Replacement text is not supported with 'push'.\n");
    return PR_OK;
    }
  if ((pat_patctl.control & ~PUSH_SUPPORTED_COMPILE_CONTROLS) != 0 ||
      (pat_patctl.control2 & ~PUSH_SUPPORTED_COMPILE_CONTROLS2) != 0)
    {
    show_controls(pat_patctl.control & ~PUSH_SUPPORTED_COMPILE_CONTROLS,
                  pat_patctl.control2 & ~PUSH_SUPPORTED_COMPILE_CONTROLS2,
      "** Ignored when compiled pattern is stacked with 'push':");
    fprintf(outfile, "\n");
    }
  if ((pat_patctl.control & PUSH_COMPILE_ONLY_CONTROLS) != 0 ||
      (pat_patctl.control2 & PUSH_COMPILE_ONLY_CONTROLS2) != 0)
    {
    show_controls(pat_patctl.control & PUSH_COMPILE_ONLY_CONTROLS,
                  pat_patctl.control2 & PUSH_COMPILE_ONLY_CONTROLS2,
      "** Applies only to compile when pattern is stacked with 'push':");
    fprintf(outfile, "\n");
    }
  }

/* Convert the input in non-8-bit modes. */

errorcode = 0;

#if defined(EBCDIC) && !EBCDIC_IO
ascii_to_ebcdic_str(pbuffer8, patlen);
#endif

#ifdef SUPPORT_PCRE2_16
if (test_mode == PCRE16_MODE) errorcode = to16(pbuffer8, utf, &patlen);
#endif

#ifdef SUPPORT_PCRE2_32
if (test_mode == PCRE32_MODE) errorcode = to32(pbuffer8, utf, &patlen);
#endif

switch(errorcode)
  {
  case -1:
  fprintf(outfile, "** Failed: invalid UTF-8 string cannot be "
    "converted to %d-bit string\n", (test_mode == PCRE16_MODE)? 16:32);
  return PR_SKIP;

  case -2:
  fprintf(outfile, "** Failed: character value greater than 0x10ffff "
    "cannot be converted to UTF\n");
  return PR_SKIP;

  case -3:
  fprintf(outfile, "** Failed: character value greater than 0xffff "
    "cannot be converted to 16-bit in non-UTF mode\n");
  return PR_SKIP;

  default:
  break;
  }

/* The pattern is now in pbuffer[8|16|32], with the length in code units in
patlen. If it is to be converted, copy the result back afterwards so that it
ends up back in the usual place. */

if (pat_patctl.convert_type != CONVERT_UNSET)
  {
  int rc;
  int convert_return = PR_OK;
  uint32_t convert_options = pat_patctl.convert_type;
  void *converted_pattern;
  PCRE2_SIZE converted_length;

  if (pat_patctl.convert_length != 0)
    {
    converted_length = pat_patctl.convert_length;
    converted_pattern = malloc(converted_length * code_unit_size);
    if (converted_pattern == NULL)
      {
      fprintf(outfile, "** Failed: malloc failed for converted pattern\n");
      return PR_SKIP;
      }
    }
  else converted_pattern = NULL;  /* Let the library allocate */

  if (utf) convert_options |= PCRE2_CONVERT_UTF;
  if ((pat_patctl.options & PCRE2_NO_UTF_CHECK) != 0)
    convert_options |= PCRE2_CONVERT_NO_UTF_CHECK;

  CONCTXCPY(con_context, default_con_context);

  if (pat_patctl.convert_glob_escape != 0)
    {
    uint32_t escape = (pat_patctl.convert_glob_escape == '0')? 0 :
      pat_patctl.convert_glob_escape;
    PCRE2_SET_GLOB_ESCAPE(rc, con_context, CHAR_INPUT(escape));
    if (rc != 0)
      {
      fprintf(outfile, "** Invalid glob escape '%c'\n",
        pat_patctl.convert_glob_escape);
      convert_return = PR_SKIP;
      goto CONVERT_FINISH;
      }
    }

  if (pat_patctl.convert_glob_separator != 0)
    {
    uint32_t separator = pat_patctl.convert_glob_separator;
    PCRE2_SET_GLOB_SEPARATOR(rc, con_context, CHAR_INPUT(separator));
    if (rc != 0)
      {
      fprintf(outfile, "** Invalid glob separator '%c'\n",
        pat_patctl.convert_glob_separator);
      convert_return = PR_SKIP;
      goto CONVERT_FINISH;
      }
    }

  PCRE2_PATTERN_CONVERT(rc, pbuffer, patlen, convert_options,
    &converted_pattern, &converted_length, con_context);

  if (rc != 0)
    {
    fprintf(outfile, "** Pattern conversion error at offset %" SIZ_FORM ": ",
      converted_length);
    convert_return = print_error_message(rc, "", "\n")? PR_SKIP:PR_ABEND;
    }

  /* Output the converted pattern, then copy it. */

  else
    {
    BOOL toolong;
    PCHARSV(converted_pattern, 0, converted_length, utf, outfile);
    fprintf(outfile, "\n");

    if (test_mode == PCRE8_MODE)
      toolong = (converted_length + 1 > pbuffer8_size);
    else if (test_mode == PCRE16_MODE)
      toolong = (2*(converted_length + 1) > pbuffer8_size);
    else  /* 32-bit */
      toolong = (4*(converted_length + 1) > pbuffer8_size);

    if (toolong)
      {
      fprintf(outfile, "** Pattern conversion is too long for the buffer\n");
      convert_return = PR_SKIP;
      }
    else
      {
      CONVERT_COPY(pbuffer, converted_pattern, converted_length + 1);
      patlen = converted_length;
      }
    }

  /* Free the converted pattern. */

  CONVERT_FINISH:
  if (pat_patctl.convert_length != 0)
    free(converted_pattern);
  else
    PCRE2_CONVERTED_PATTERN_FREE(converted_pattern);

  /* Return if conversion was unsuccessful. */

  if (convert_return != PR_OK) return convert_return;
  }

/* By default we pass a zero-terminated pattern, but a length is passed if
"use_length" was specified or this is a hex pattern (which might contain binary
zeros). When valgrind is supported, arrange for the unused part of the buffer
to be marked as no access. */

valgrind_access_length = patlen;
if ((pat_patctl.control & (CTL_HEXPAT|CTL_USE_LENGTH)) == 0)
  {
  patlen = PCRE2_ZERO_TERMINATED;
  valgrind_access_length += 1;  /* For the terminating zero */
  }

#ifdef SUPPORT_VALGRIND
#ifdef SUPPORT_PCRE2_8
if (test_mode == PCRE8_MODE && pbuffer8 != NULL)
  {
  VALGRIND_MAKE_MEM_NOACCESS(pbuffer8 + valgrind_access_length,
    pbuffer8_size - valgrind_access_length);
  }
#endif
#ifdef SUPPORT_PCRE2_16
if (test_mode == PCRE16_MODE && pbuffer16 != NULL)
  {
  VALGRIND_MAKE_MEM_NOACCESS(pbuffer16 + valgrind_access_length,
    pbuffer16_size - valgrind_access_length*sizeof(uint16_t));
  }
#endif
#ifdef SUPPORT_PCRE2_32
if (test_mode == PCRE32_MODE && pbuffer32 != NULL)
  {
  VALGRIND_MAKE_MEM_NOACCESS(pbuffer32 + valgrind_access_length,
    pbuffer32_size - valgrind_access_length*sizeof(uint32_t));
  }
#endif
#else  /* Valgrind not supported */
(void)valgrind_access_length;  /* Avoid compiler warning */
#endif

/* If #newline_default has been used and the library was not compiled with an
appropriate default newline setting, local_newline_default will be non-zero. We
use this if there is no explicit newline modifier. */

if ((pat_patctl.control2 & CTL2_NL_SET) == 0 && local_newline_default != 0)
  {
  SETFLD(pat_context, newline_convention, local_newline_default);
  }

/* The null_context modifier is used to test calling pcre2_compile() with a
NULL context. */

use_pat_context = ((pat_patctl.control & CTL_NULLCONTEXT) != 0)?
  NULL : PTR(pat_context);

/* If PCRE2_LITERAL is set, set use_forbid_utf zero because PCRE2_NEVER_UTF
and PCRE2_NEVER_UCP are invalid with it. */

if ((pat_patctl.options & PCRE2_LITERAL) != 0) use_forbid_utf = 0;

/* Set use_pbuffer to the input buffer, or leave it as NULL if requested. */

if ((pat_patctl.control2 & CTL2_NULL_PATTERN) == 0)
  {
#ifdef SUPPORT_PCRE2_8
  if (test_mode == PCRE8_MODE) use_pbuffer = pbuffer8;
#endif
#ifdef SUPPORT_PCRE2_16
  if (test_mode == PCRE16_MODE) use_pbuffer = pbuffer16;
#endif
#ifdef SUPPORT_PCRE2_32
  if (test_mode == PCRE32_MODE) use_pbuffer = pbuffer32;
#endif
  }

/* Compile many times when timing. */

if (timeit > 0)
  {
  int i;
  clock_t time_taken = 0;
  for (i = 0; i < timeit; i++)
    {
    clock_t start_time = clock();
    PCRE2_COMPILE(compiled_code, use_pbuffer, patlen,
      pat_patctl.options|use_forbid_utf, &errorcode, &erroroffset,
        use_pat_context);
    time_taken += clock() - start_time;
    if (TEST(compiled_code, !=, NULL))
      { SUB1(pcre2_code_free, compiled_code); }
    }
  total_compile_time += time_taken;
  fprintf(outfile, "Compile time %8.4f microseconds\n",
    ((1000000 / CLOCKS_PER_SEC) * (double)time_taken) / timeit);
  }

/* A final compile that is used "for real". */

mallocs_called = 0;
PCRE2_COMPILE(compiled_code, use_pbuffer, patlen,
  pat_patctl.options|use_forbid_utf, &errorcode, &erroroffset, use_pat_context);

/* For malloc testing, we repeat the compilation. */

if (malloc_testing)
  {
  for (int i = 0, target_mallocs = mallocs_called; i <= target_mallocs; i++)
    {
    if (TEST(compiled_code, !=, NULL))
      { SUB1(pcre2_code_free, compiled_code); }

    errorcode = 0;
    erroroffset = 0;
    mallocs_until_failure = i;
    PCRE2_COMPILE(compiled_code, use_pbuffer, patlen,
      pat_patctl.options|use_forbid_utf, &errorcode, &erroroffset, use_pat_context);
    mallocs_until_failure = INT_MAX;

    if (i < target_mallocs &&
        !(TEST(compiled_code, ==, NULL) && errorcode == PCRE2_ERROR_HEAP_FAILED))
      {
      fprintf(outfile, "** malloc() compile test did not fail as expected (%d)\n",
              errorcode);
      return PR_ABEND;
      }
    }
  }

/* If valgrind is supported, mark the pbuffer as accessible again. We leave the
pattern in the test-mode's buffer defined because it may be read from a callout
during matching. */

#ifdef SUPPORT_VALGRIND
#ifdef SUPPORT_PCRE2_8
if (test_mode == PCRE8_MODE)
  {
  VALGRIND_MAKE_MEM_UNDEFINED(pbuffer8 + valgrind_access_length,
    pbuffer8_size - valgrind_access_length);
  }
else
  {
  VALGRIND_MAKE_MEM_UNDEFINED(pbuffer8, pbuffer8_size);
  }
#endif
#ifdef SUPPORT_PCRE2_16
if (test_mode == PCRE16_MODE)
  {
  VALGRIND_MAKE_MEM_UNDEFINED(pbuffer16 + valgrind_access_length,
    pbuffer16_size - valgrind_access_length*sizeof(uint16_t));
  }
else
  {
  VALGRIND_MAKE_MEM_UNDEFINED(pbuffer16, pbuffer16_size);
  }
#endif
#ifdef SUPPORT_PCRE2_32
if (test_mode == PCRE32_MODE)
  {
  VALGRIND_MAKE_MEM_UNDEFINED(pbuffer32 + valgrind_access_length,
    pbuffer32_size - valgrind_access_length*sizeof(uint32_t));
  }
else
  {
  VALGRIND_MAKE_MEM_UNDEFINED(pbuffer32, pbuffer32_size);
  }
#endif
#endif

/* Call the JIT compiler if requested. When timing, or testing malloc failures,
we must free and recompile the pattern each time because that is the only way to
free the JIT compiled code. We know that compilation will always succeed. */

if (TEST(compiled_code, !=, NULL) && pat_patctl.jit != 0)
  {
  if (timeit > 0)
    {
    int i;
    clock_t time_taken = 0;

    for (i = 0; i < timeit; i++)
      {
      clock_t start_time = clock();
      PCRE2_JIT_COMPILE(jitrc, compiled_code, pat_patctl.jit);
      time_taken += clock() - start_time;

      SUB1(pcre2_code_free, compiled_code);
      PCRE2_COMPILE(compiled_code, use_pbuffer, patlen,
        pat_patctl.options|use_forbid_utf, &errorcode, &erroroffset,
        use_pat_context);
      if (TEST(compiled_code, ==, NULL))
        {
        fprintf(outfile, "** Unexpected - pattern compilation not successful\n");
        return PR_ABEND;
        }

      if (jitrc != 0)
        {
        fprintf(outfile, "JIT compilation was not successful");
        if (!print_error_message(jitrc, " (", ")\n")) return PR_ABEND;
        break;
        }
      }
    total_jit_compile_time += time_taken;
    if (jitrc == 0)
      fprintf(outfile, "JIT compile  %8.4f microseconds\n",
        ((1000000 / CLOCKS_PER_SEC) * (double)time_taken) / timeit);
    }

  mallocs_called = 0;
  PCRE2_JIT_COMPILE(jitrc, compiled_code, pat_patctl.jit);

  /* For malloc testing, we repeat the compilation. */

  if (malloc_testing)
    {
    for (int i = 0, target_mallocs = mallocs_called; i <= target_mallocs; i++)
      {
      SUB1(pcre2_code_free, compiled_code);
      PCRE2_COMPILE(compiled_code, use_pbuffer, patlen,
        pat_patctl.options|use_forbid_utf, &errorcode, &erroroffset,
        use_pat_context);
      if (TEST(compiled_code, ==, NULL))
        {
        fprintf(outfile, "** Unexpected - pattern compilation not successful\n");
        return PR_ABEND;
        }

      mallocs_until_failure = i;
      PCRE2_JIT_COMPILE(jitrc, compiled_code, pat_patctl.jit);
      mallocs_until_failure = INT_MAX;

      if (i < target_mallocs && jitrc != PCRE2_ERROR_NOMEMORY)
        {
        fprintf(outfile, "** malloc() JIT compile test did not fail as expected (%d)\n",
                jitrc);
        return PR_ABEND;
        }
      }
    }

  /* Check whether JIT compilation failed; but continue with an error message
  if not. */

  if (jitrc != 0 && (pat_patctl.control & CTL_JITVERIFY) != 0)
    {
    fprintf(outfile, "JIT compilation was not successful");
    if (!print_error_message(jitrc, " (", ")\n")) return PR_ABEND;
    }
  }

/* Compilation failed; go back for another re, skipping to blank line
if non-interactive. */

if (TEST(compiled_code, ==, NULL))
  {
  int direction = error_direction(errorcode, erroroffset);

  fprintf(outfile, "Failed: error %d at offset %d: ", errorcode,
    (int)erroroffset);
  if (!print_error_message(errorcode, "", "\n")) return PR_ABEND;

  /* It's important that the erroroffset doesn't slice halfway through a UTF-8
  or UTF-16 character. We can verify this by checking that the input left of the
  erroroffset is valid. Note that if the input is invalid (which is exercised in
  some tests) then the offset will be positioned with the valid part to the left
  of erroroffset. */

#ifdef SUPPORT_PCRE2_8
  if (test_mode == PCRE8_MODE && utf)
    {
    uint32_t cc;
    int n = 1;
    for (uint8_t *q = pbuffer8, *q_end = q + erroroffset; q < q_end && n > 0; q += n)
      n = utf8_to_ord(q, q_end, &cc);
    if (n <= 0)
      {
      fprintf(outfile, "** Erroroffset %d splits a UTF-8 character\n", (int)erroroffset);
      return PR_ABEND;
      }
    }
#endif
#ifdef SUPPORT_PCRE2_16
  if (test_mode == PCRE16_MODE && utf)
    {
    uint32_t cc;
    int n = 1;
    for (uint16_t *q = pbuffer16, *q_end = q + erroroffset; q < q_end && n > 0; q += n)
      n = utf16_to_ord(q, q_end, &cc);
    if (n <= 0)
      {
      fprintf(outfile, "** Erroroffset %d splits a UTF-16 character\n", (int)erroroffset);
      return PR_ABEND;
      }
    }
#endif

  /* Print the surrounding context around the erroroffset. */

  if (direction < 0)
    {
    fprintf(outfile, "** Error code %d not implemented in error_direction().\n", errorcode);
    fprintf(outfile, "   error_direction() should usually return '1' for newly-added errors,\n");
    fprintf(outfile, "   and the offset should be just to the right of the bad character.\n");
    return PR_ABEND;
    }

  else if (direction != 0)
    {
    PCRE2_SIZE full_patlen = (patlen != PCRE2_ZERO_TERMINATED)? patlen :
        STRLEN(CASTVAR(void *, pbuffer));

    fprintf(outfile, "        here: ");
    if (erroroffset > 0)
      {
      PTRUNCV(CASTVAR(void *, pbuffer), full_patlen, erroroffset, TRUE, utf, outfile);
      fprintf(outfile, " ");
      }
    fprintf(outfile, (direction == 1)? "|<--|" : (direction == 2)? "|-->|" : "|<-->|");
    if (erroroffset < full_patlen)
      {
      fprintf(outfile, " ");
      PTRUNCV(CASTVAR(void *, pbuffer), full_patlen, erroroffset, FALSE, utf, outfile);
      }
    fprintf(outfile, "\n");
    }

  else if (erroroffset != 0)
    {
    fprintf(outfile, "** Unexpected non-zero erroroffset %d for error code %d\n",
      (int)erroroffset, errorcode);
    return PR_ABEND;
    }

  return PR_SKIP;
  }

/* If forbid_utf is non-zero, we are running a non-UTF test. UTF and UCP are
locked out at compile time, but we must also check for occurrences of \P, \p,
and \X, which are only supported when Unicode is supported. */

if (forbid_utf != 0)
  {
  if ((FLD(compiled_code, flags) & PCRE2_HASBKPORX) != 0)
    {
    fprintf(outfile, "** \\P, \\p, and \\X are not allowed after the "
      "#forbid_utf command\n");
    return PR_SKIP;
    }
  }

/* Remember the maximum lookbehind, for partial matching. */

if (pattern_info(PCRE2_INFO_MAXLOOKBEHIND, &maxlookbehind, FALSE) != 0)
  return PR_ABEND;

/* Remember the number of captures. */

if (pattern_info(PCRE2_INFO_CAPTURECOUNT, &maxcapcount, FALSE) < 0)
  return PR_ABEND;

/* If an explicit newline modifier was given, set the information flag in the
pattern so that it is preserved over push/pop. */

if ((pat_patctl.control2 & CTL2_NL_SET) != 0)
  {
  SETFLD(compiled_code, flags, FLD(compiled_code, flags) | PCRE2_NL_SET);
  }

/* Output code size and other information if requested. */

if ((pat_patctl.control & CTL_MEMORY) != 0) show_memory_info();
if ((pat_patctl.control2 & CTL2_FRAMESIZE) != 0) show_framesize();
if ((pat_patctl.control & CTL_ANYINFO) != 0)
  {
  int rc = show_pattern_info();
  if (rc != PR_OK) return rc;
  }

/* The "push" control requests that the compiled pattern be remembered on a
stack. This is mainly for testing the serialization functionality. */

if ((pat_patctl.control & CTL_PUSH) != 0)
  {
  if (patstacknext >= PATSTACKSIZE)
    {
    fprintf(outfile, "** Too many pushed patterns (max %d)\n", PATSTACKSIZE);
    return PR_ABEND;
    }
  patstack[patstacknext++] = PTR(compiled_code);
  SET(compiled_code, NULL);
  }

/* The "pushcopy" and "pushtablescopy" controls are similar, but push a
copy of the pattern, the latter with a copy of its character tables. This tests
the pcre2_code_copy() and pcre2_code_copy_with_tables() functions. */

if ((pat_patctl.control & (CTL_PUSHCOPY|CTL_PUSHTABLESCOPY)) != 0)
  {
  if (patstacknext >= PATSTACKSIZE)
    {
    fprintf(outfile, "** Too many pushed patterns (max %d)\n", PATSTACKSIZE);
    return PR_ABEND;
    }
  if ((pat_patctl.control & CTL_PUSHCOPY) != 0)
    {
    PCRE2_CODE_COPY_TO_VOID(patstack[patstacknext++], compiled_code);
    }
  else
    {
    PCRE2_CODE_COPY_WITH_TABLES_TO_VOID(patstack[patstacknext++],
      compiled_code); }
  }

return PR_OK;
}



/* Helper to test for an active pattern. */

static BOOL
have_active_pattern(void)
{
return compiled_code != NULL;
}


/* Helper to free (and null-out) the active pattern. */

static void
free_active_pattern(void)
{
if (compiled_code != NULL)
  {
  pcre2_code_free(compiled_code);
  compiled_code = NULL;
  }
}



/*************************************************
*          Check heap, match or depth limit      *
*************************************************/

/* This is used for DFA, normal, and JIT fast matching. For DFA matching it
should only be called with the third argument set to PCRE2_ERROR_DEPTHLIMIT.

Arguments:
  pp        the subject string
  ulen      length of subject or PCRE2_ZERO_TERMINATED
  errnumber defines which limit to test
  msg       string to include in final message

Returns:    the return from the final match function call
*/

static int
check_match_limit(uint8_t *pp, PCRE2_SIZE ulen, int errnumber, const char *msg)
{
int capcount;
uint32_t min = 0;
uint32_t mid = 64;
uint32_t max = UINT32_MAX;

PCRE2_SET_MATCH_LIMIT(dat_context, max);
PCRE2_SET_DEPTH_LIMIT(dat_context, max);
PCRE2_SET_HEAP_LIMIT(dat_context, max);

for (;;)
  {
  uint32_t stack_start = 0;

  /* If we are checking the heap limit, free any frames vector that is cached
  in the match_data so we always start without one. */

  if (errnumber == PCRE2_ERROR_HEAPLIMIT)
    {
    PCRE2_SET_HEAP_LIMIT(dat_context, mid);

#ifdef SUPPORT_PCRE2_8
    if (code_unit_size == 1)
      {
      match_data8->memctl.free(match_data8->heapframes,
        match_data8->memctl.memory_data);
      match_data8->heapframes = NULL;
      match_data8->heapframes_size = 0;
      }
#endif

#ifdef SUPPORT_PCRE2_16
    if (code_unit_size == 2)
      {
      match_data16->memctl.free(match_data16->heapframes,
        match_data16->memctl.memory_data);
      match_data16->heapframes = NULL;
      match_data16->heapframes_size = 0;
      }
#endif

#ifdef SUPPORT_PCRE2_32
    if (code_unit_size == 4)
      {
      match_data32->memctl.free(match_data32->heapframes,
        match_data32->memctl.memory_data);
      match_data32->heapframes = NULL;
      match_data32->heapframes_size = 0;
      }
#endif
    }

  /* No need to mess with the frames vector for match or depth limits. */

  else if (errnumber == PCRE2_ERROR_MATCHLIMIT)
    {
    PCRE2_SET_MATCH_LIMIT(dat_context, mid);
    }
  else
    {
    PCRE2_SET_DEPTH_LIMIT(dat_context, mid);
    }

  /* Do the appropriate match */

  if ((dat_datctl.control & CTL_DFA) != 0)
    {
    stack_start = DFA_START_RWS_SIZE/1024;
    if (dfa_workspace == NULL)
      dfa_workspace = (int *)malloc(DFA_WS_DIMENSION*sizeof(int));
    if (dfa_matched++ == 0)
      dfa_workspace[0] = -1;  /* To catch bad restart */
    PCRE2_DFA_MATCH(capcount, compiled_code, pp, ulen, dat_datctl.offset,
      dat_datctl.options, match_data,
      PTR(dat_context), dfa_workspace, DFA_WS_DIMENSION);
    }

  else if ((pat_patctl.control & CTL_JITFAST) != 0)
    PCRE2_JIT_MATCH(capcount, compiled_code, pp, ulen, dat_datctl.offset,
      dat_datctl.options, match_data, PTR(dat_context));

  else
    {
    PCRE2_MATCH(capcount, compiled_code, pp, ulen, dat_datctl.offset,
      dat_datctl.options, match_data, PTR(dat_context));
    }

  if (capcount == errnumber)
    {
    if ((mid & 0x80000000u) != 0)
      {
      fprintf(outfile, "Can't find minimum %s limit: check pattern for "
        "restriction\n", msg);
      break;
      }

    min = mid;
    mid = (mid == max - 1)? max : (max != UINT32_MAX)? (min + max)/2 : mid*2;
    }
  else if (capcount >= 0 ||
           capcount == PCRE2_ERROR_NOMATCH ||
           capcount == PCRE2_ERROR_PARTIAL)
    {
    /* If we've not hit the error with a heap limit less than the size of the
    initial stack frame vector (for pcre2_match()) or the initial stack
    workspace vector (for pcre2_dfa_match()), the heap is not being used, so
    the minimum limit is zero; there's no need to go on. The other limits are
    always greater than zero. */

    if (errnumber == PCRE2_ERROR_HEAPLIMIT && mid < stack_start)
      {
      fprintf(outfile, "Minimum %s limit = 0\n", msg);
      break;
      }
    if (mid == min + 1)
      {
      fprintf(outfile, "Minimum %s limit = %d\n", msg, mid);
      break;
      }
    max = mid;
    mid = (min + max)/2;
    }
  else break;    /* Some other error */
  }

return capcount;
}



/*************************************************
*        Substitute callout function             *
*************************************************/

/* Called from pcre2_substitute() when the substitute_callout modifier is set.
Print out the data that is passed back.

Arguments:
  scb         pointer to substitute callout block
  data_ptr    callout data

Returns:      nothing
*/

// XXX fix random choice of _8
static int
substitute_callout_function(pcre2_substitute_callout_block_8 *scb,
  void *data_ptr)
{
int yield = 0;
BOOL utf = (FLD(compiled_code, overall_options) & PCRE2_UTF) != 0;
(void)data_ptr;   /* Not used */

fprintf(outfile, "%2d(%d) Old %" SIZ_FORM " %" SIZ_FORM " \"",
  scb->subscount, scb->oveccount,
  scb->ovector[0], scb->ovector[1]);

PCHARSV(scb->input, scb->ovector[0], scb->ovector[1] - scb->ovector[0],
  utf, outfile);

fprintf(outfile, "\" New %" SIZ_FORM " %" SIZ_FORM " \"",
  scb->output_offsets[0], scb->output_offsets[1]);

PCHARSV(scb->output, scb->output_offsets[0],
  scb->output_offsets[1] - scb->output_offsets[0], utf, outfile);

if (scb->subscount == dat_datctl.substitute_stop)
  {
  yield = -1;
  fprintf(outfile, " STOPPED");
  }
else if (scb->subscount == dat_datctl.substitute_skip)
  {
  yield = +1;
  fprintf(outfile, " SKIPPED");
  }

fprintf(outfile, "\"\n");
return yield;
}



/*************************************************
*        Substitute case callout function        *
*************************************************/

/* Called from pcre2_substitute() when the substitute_case_callout
modifier is set. The substitute callout block is not identical for all code unit
widths, so we have to duplicate the function for each supported width.

Arguments:
  input          the input character
  input_len      the length of the input
  output         the output buffer
  output_cap     the output buffer capacity
  to_case        the case conversion type
  data_ptr       callout data (unused)

Returns:         the number of code units of the output
*/

static PCRE2_SIZE
G(substitute_case_callout_function,BITS)(
  G(PCRE2_SPTR,BITS) input, PCRE2_SIZE input_len,
  G(PCRE2_UCHAR,BITS) *output, PCRE2_SIZE output_cap,
  int to_case, void *data_ptr)
{
G(PCRE2_UCHAR,BITS) buf[16];
G(PCRE2_SPTR,BITS) input_copy;
PCRE2_SIZE written = 0;

(void)data_ptr;   /* Not used */

if (input_len > sizeof(buf)/sizeof(*buf))
  {
  G(PCRE2_UCHAR,BITS) *input_buf = malloc(
      input_len * sizeof(G(PCRE2_UCHAR,BITS)));
  if (input_buf == NULL) return ~(PCRE2_SIZE)0;
  memcpy(input_buf, input, input_len * sizeof(G(PCRE2_UCHAR,BITS)));
  input_copy = input_buf;
  }
else
  {
  memcpy(buf, input, input_len * sizeof(G(PCRE2_UCHAR,BITS)));
  input_copy = buf;
  }

for (PCRE2_SIZE i = 0; i < input_len; )
  {
  int num_in = i + 1 < input_len ? 2 : 1;
  uint32_t c1 = input_copy[i];
  uint32_t c2 = i + 1 < input_len ? input_copy[i + 1] : 0;
  int num_read;
  int num_write;

  if (!case_transform(to_case, num_in, &num_read, &num_write, &c1, &c2))
    {
    written = ~(PCRE2_SIZE)0;
    goto END;
    }

  i += num_read;
  if (to_case == PCRE2_SUBSTITUTE_CASE_TITLE_FIRST)
    to_case = PCRE2_SUBSTITUTE_CASE_LOWER;

  if (written + num_write > output_cap)
    {
    written += num_write;
    }
  else
    {
    if (num_write > 0) output[written++] = c1;
    if (num_write > 1) output[written++] = c2;
    }
  }

END:
if (input_copy != buf) free((G(PCRE2_UCHAR,BITS) *)input_copy);

/* Let's be maximally cruel. The case callout is allowed to leave the output
buffer in any state at all if it overflows, so let's use random garbage. */
if (written > output_cap)
  memset(output, time(NULL) & 1 ? 0xcd : 0xdc,
         output_cap * sizeof(G(PCRE2_UCHAR,BITS)));

return written;
}



/*************************************************
*              Callout function                  *
*************************************************/

/* Called from a PCRE2 library as a result of the (?C) item. We print out where
we are in the match (unless suppressed). Yield zero unless more callouts than
the fail count, or the callout data is not zero. The only differences in the
callout block for different code unit widths are that the pointers to the
subject, the most recent MARK, and a callout argument string point to strings
of the appropriate width. Casts can be used to deal with this.

Arguments:
  cb                a pointer to a callout block
  callout_data_ptr  the provided callout data

Returns:            0 or 1 or an error, as determined by settings
*/

static int
callout_function(pcre2_callout_block_8 *cb, void *callout_data_ptr)
{
FILE *f, *fdefault;
uint32_t i, pre_start, post_start, subject_length;
PCRE2_SIZE current_position;
BOOL utf = (FLD(compiled_code, overall_options) & PCRE2_UTF) != 0;
BOOL callout_capture = (dat_datctl.control & CTL_CALLOUT_CAPTURE) != 0;
BOOL callout_where = (dat_datctl.control2 & CTL2_CALLOUT_NO_WHERE) == 0;

/* The FILE f is used for echoing the subject string if it is non-NULL. This
happens only once in simple cases, but we want to repeat after any additional
output caused by CALLOUT_EXTRA. */

fdefault = (!first_callout && !callout_capture && cb->callout_string == NULL)?
  NULL : outfile;

if ((dat_datctl.control2 & CTL2_CALLOUT_EXTRA) != 0)
  {
  f = outfile;
  switch (cb->callout_flags)
    {
    case PCRE2_CALLOUT_BACKTRACK:
    fprintf(f, "Backtrack\n");
    break;

    case PCRE2_CALLOUT_STARTMATCH|PCRE2_CALLOUT_BACKTRACK:
    fprintf(f, "Backtrack\nNo other matching paths\n");
    PCRE2_FALLTHROUGH /* Fall through */

    case PCRE2_CALLOUT_STARTMATCH:
    fprintf(f, "New match attempt\n");
    break;

    default:
    f = fdefault;
    break;
    }
  }
else f = fdefault;

/* For a callout with a string argument, show the string first because there
isn't a tidy way to fit it in the rest of the data. */

if (cb->callout_string != NULL)
  {
  uint32_t delimiter = CODE_UNIT(cb->callout_string, -1);
  fprintf(outfile, "Callout (%" SIZ_FORM "): %c",
    cb->callout_string_offset, CHAR_OUTPUT(delimiter));
  PCHARSV(cb->callout_string, 0,
    cb->callout_string_length, utf, outfile);
  for (i = 0; callout_start_delims[i] != 0; i++)
    if (delimiter == callout_start_delims[i])
      {
      delimiter = callout_end_delims[i];
      break;
      }
  fprintf(outfile, "%c", CHAR_OUTPUT(delimiter));
  if (!callout_capture) fprintf(outfile, "\n");
  }

/* Show captured strings if required */

if (callout_capture)
  {
  if (cb->callout_string == NULL)
    fprintf(outfile, "Callout %d:", cb->callout_number);
  fprintf(outfile, " last capture = %d\n", cb->capture_last);
  for (i = 2; i < cb->capture_top * 2; i += 2)
    {
    fprintf(outfile, "%2d: ", i/2);
    if (cb->offset_vector[i] == PCRE2_UNSET)
      fprintf(outfile, "<unset>");
    else
      {
      PCHARSV(cb->subject, cb->offset_vector[i],
        cb->offset_vector[i+1] - cb->offset_vector[i], utf, f);
      }
    fprintf(outfile, "\n");
    }
  }

/* Unless suppressed, re-print the subject in canonical form (with escapes for
non-printing characters), the first time, or if giving full details. On
subsequent calls in the same match, we use PCHARS() just to find the printed
lengths of the substrings. */

if (callout_where)
  {
  if (f != NULL) fprintf(f, "--->");

  /* The subject before the match start. */

  PCHARS(pre_start, cb->subject, 0, cb->start_match, utf, f);

  /* If a lookbehind is involved, the current position may be earlier than the
  match start. If so, use the match start instead. */

  current_position = (cb->current_position >= cb->start_match)?
    cb->current_position : cb->start_match;

  /* The subject between the match start and the current position. */

  PCHARS(post_start, cb->subject, cb->start_match,
    current_position - cb->start_match, utf, f);

  /* Print from the current position to the end. */

  PCHARSV(cb->subject, current_position, cb->subject_length - current_position,
    utf, f);

  /* Calculate the total subject printed length (no print). */

  PCHARS(subject_length, cb->subject, 0, cb->subject_length, utf, NULL);

  if (f != NULL) fprintf(f, "\n");

  /* For automatic callouts, show the pattern offset. Otherwise, for a
  numerical callout whose number has not already been shown with captured
  strings, show the number here. A callout with a string argument has been
  displayed above. */

  if (cb->callout_number == 255)
    {
    fprintf(outfile, "%+3d ", (int)cb->pattern_position);
    if (cb->pattern_position > 99) fprintf(outfile, "\n    ");
    }
  else
    {
    if (callout_capture || cb->callout_string != NULL) fprintf(outfile, "    ");
      else fprintf(outfile, "%3d ", cb->callout_number);
    }

  /* Now show position indicators */

  for (i = 0; i < pre_start; i++) fprintf(outfile, " ");
  fprintf(outfile, "^");

  if (post_start > 0)
    {
    for (i = 0; i < post_start - 1; i++) fprintf(outfile, " ");
    fprintf(outfile, "^");
    }

  for (i = 0; i < subject_length - pre_start - post_start + 4; i++)
    fprintf(outfile, " ");

  if (cb->next_item_length != 0)
    {
    PCHARSV(CASTVAR(void *, pbuffer), cb->pattern_position,
            (int)(cb->next_item_length), utf, outfile);
    }
  else
    fprintf(outfile, "End of pattern");

  fprintf(outfile, "\n");
  }

first_callout = FALSE;

/* Show any mark info */

if (cb->mark != last_callout_mark)
  {
  if (cb->mark == NULL)
    fprintf(outfile, "Latest Mark: <unset>\n");
  else
    {
    fprintf(outfile, "Latest Mark: ");
    PCHARSV(cb->mark, -1, -1, utf, outfile);
    putc('\n', outfile);
    }
  last_callout_mark = cb->mark;
  }

/* Show callout data */

if (callout_data_ptr != NULL)
  {
  int callout_data = *((int32_t *)callout_data_ptr);
  if (callout_data != 0)
    {
    fprintf(outfile, "Callout data = %d\n", callout_data);
    return callout_data;
    }
  }

/* Keep count and give the appropriate return code */

callout_count++;

if (cb->callout_number == dat_datctl.cerror[0] &&
    callout_count >= dat_datctl.cerror[1])
  return PCRE2_ERROR_CALLOUT;

if (cb->callout_number == dat_datctl.cfail[0] &&
    callout_count >= dat_datctl.cfail[1])
  return 1;

return 0;
}



/*************************************************
*       Handle *MARK and copy/get tests          *
*************************************************/

/* This function is called after complete and partial matches. It runs the
tests for substring extraction.

Arguments:
  utf       TRUE for utf
  capcount  return from pcre2_match()

Returns:    FALSE if print_error_message() fails
*/

static BOOL
copy_and_get(BOOL utf, int capcount)
{
int i;
uint8_t *nptr;

/* Test copy strings by number */

for (i = 0; i < MAXCPYGET && dat_datctl.copy_numbers[i] >= 0; i++)
  {
  int rc;
  PCRE2_SIZE length, length2;
  uint32_t copybuffer[256];
  uint32_t n = (uint32_t)(dat_datctl.copy_numbers[i]);
  length = sizeof(copybuffer)/code_unit_size;
  PCRE2_SUBSTRING_COPY_BYNUMBER(rc, match_data, n, copybuffer, &length);
  if (rc < 0)
    {
    fprintf(outfile, "Copy substring %d failed (%d): ", n, rc);
    if (!print_error_message(rc, "", "\n")) return FALSE;
    }
  else
    {
    PCRE2_SUBSTRING_LENGTH_BYNUMBER(rc, match_data, n, &length2);
    if (rc < 0)
      {
      fprintf(outfile, "Get substring %d length failed (%d): ", n, rc);
      if (!print_error_message(rc, "", "\n")) return FALSE;
      }
    else if (length2 != length)
      {
      fprintf(outfile, "Mismatched substring lengths: %"
        SIZ_FORM " %" SIZ_FORM "\n", length, length2);
      }
    fprintf(outfile, "%2dC ", n);
    PCHARSV(copybuffer, 0, length, utf, outfile);
    fprintf(outfile, " (%" SIZ_FORM ")\n", length);
    }
  }

/* Test copy strings by name */

nptr = dat_datctl.copy_names;
for (;;)
  {
  int rc;
  int groupnumber;
  PCRE2_SIZE length, length2;
  uint32_t copybuffer[256];
  size_t namelen = strlen((const char *)nptr);
#if defined SUPPORT_PCRE2_16 || defined SUPPORT_PCRE2_32
  PCRE2_SIZE cnl = namelen;
#endif
  if (namelen == 0) break;

#ifdef SUPPORT_PCRE2_8
  if (test_mode == PCRE8_MODE) strcpy((char *)pbuffer8, (char *)nptr);
#endif
#if defined(EBCDIC) && !EBCDIC_IO
  ascii_to_ebcdic_str(pbuffer8, namelen);
#endif
#ifdef SUPPORT_PCRE2_16
  if (test_mode == PCRE16_MODE)(void)to16(nptr, utf, &cnl);
#endif
#ifdef SUPPORT_PCRE2_32
  if (test_mode == PCRE32_MODE)(void)to32(nptr, utf, &cnl);
#endif

  PCRE2_SUBSTRING_NUMBER_FROM_NAME(groupnumber, compiled_code, pbuffer);
  if (groupnumber < 0 && groupnumber != PCRE2_ERROR_NOUNIQUESUBSTRING)
    fprintf(outfile, "Number not found for group \"%s\"\n", nptr);

  length = sizeof(copybuffer)/code_unit_size;
  PCRE2_SUBSTRING_COPY_BYNAME(rc, match_data, pbuffer, copybuffer, &length);
  if (rc < 0)
    {
    fprintf(outfile, "Copy substring \"%s\" failed (%d): ", nptr, rc);
    if (!print_error_message(rc, "", "\n")) return FALSE;
    }
  else
    {
    PCRE2_SUBSTRING_LENGTH_BYNAME(rc, match_data, pbuffer, &length2);
    if (rc < 0)
      {
      fprintf(outfile, "Get substring \"%s\" length failed (%d): ", nptr, rc);
      if (!print_error_message(rc, "", "\n")) return FALSE;
      }
    else if (length2 != length)
      {
      fprintf(outfile, "Mismatched substring lengths: %"
        SIZ_FORM " %" SIZ_FORM "\n", length, length2);
      }
    fprintf(outfile, "  C ");
    PCHARSV(copybuffer, 0, length, utf, outfile);
    fprintf(outfile, " (%" SIZ_FORM ") %s", length, nptr);
    if (groupnumber >= 0) fprintf(outfile, " (group %d)\n", groupnumber);
      else fprintf(outfile, " (non-unique)\n");
    }
  nptr += namelen + 1;
  }

/* Test get strings by number */

for (i = 0; i < MAXCPYGET && dat_datctl.get_numbers[i] >= 0; i++)
  {
  int rc;
  PCRE2_SIZE length;
  void *gotbuffer;
  uint32_t n = (uint32_t)(dat_datctl.get_numbers[i]);
  PCRE2_SUBSTRING_GET_BYNUMBER(rc, match_data, n, &gotbuffer, &length);
  if (rc < 0)
    {
    fprintf(outfile, "Get substring %d failed (%d): ", n, rc);
    if (!print_error_message(rc, "", "\n")) return FALSE;
    }
  else
    {
    fprintf(outfile, "%2dG ", n);
    PCHARSV(gotbuffer, 0, length, utf, outfile);
    fprintf(outfile, " (%" SIZ_FORM ")\n", length);
    PCRE2_SUBSTRING_FREE(gotbuffer);
    }
  }

/* Test get strings by name */

nptr = dat_datctl.get_names;
for (;;)
  {
  PCRE2_SIZE length;
  void *gotbuffer;
  int rc;
  int groupnumber;
  size_t namelen = strlen((const char *)nptr);
#if defined SUPPORT_PCRE2_16 || defined SUPPORT_PCRE2_32
  PCRE2_SIZE cnl = namelen;
#endif
  if (namelen == 0) break;

#ifdef SUPPORT_PCRE2_8
  if (test_mode == PCRE8_MODE) strcpy((char *)pbuffer8, (char *)nptr);
#endif
#if defined(EBCDIC) && !EBCDIC_IO
  ascii_to_ebcdic_str(pbuffer8, namelen);
#endif
#ifdef SUPPORT_PCRE2_16
  if (test_mode == PCRE16_MODE)(void)to16(nptr, utf, &cnl);
#endif
#ifdef SUPPORT_PCRE2_32
  if (test_mode == PCRE32_MODE)(void)to32(nptr, utf, &cnl);
#endif

  PCRE2_SUBSTRING_NUMBER_FROM_NAME(groupnumber, compiled_code, pbuffer);
  if (groupnumber < 0 && groupnumber != PCRE2_ERROR_NOUNIQUESUBSTRING)
    fprintf(outfile, "Number not found for group \"%s\"\n", nptr);

  PCRE2_SUBSTRING_GET_BYNAME(rc, match_data, pbuffer, &gotbuffer, &length);
  if (rc < 0)
    {
    fprintf(outfile, "Get substring \"%s\" failed (%d): ", nptr, rc);
    if (!print_error_message(rc, "", "\n")) return FALSE;
    }
  else
    {
    fprintf(outfile, "  G ");
    PCHARSV(gotbuffer, 0, length, utf, outfile);
    fprintf(outfile, " (%" SIZ_FORM ") %s", length, nptr);
    if (groupnumber >= 0) fprintf(outfile, " (group %d)\n", groupnumber);
      else fprintf(outfile, " (non-unique)\n");
    PCRE2_SUBSTRING_FREE(gotbuffer);
    }
  nptr += namelen + 1;
  }

/* Test getting the complete list of captured strings. */

if ((dat_datctl.control & CTL_GETALL) != 0)
  {
  int rc;
  void **stringlist;
  PCRE2_SIZE *lengths;
  PCRE2_SUBSTRING_LIST_GET(rc, match_data, &stringlist, &lengths);
  if (rc < 0)
    {
    fprintf(outfile, "get substring list failed (%d): ", rc);
    if (!print_error_message(rc, "", "\n")) return FALSE;
    }
  else
    {
    for (i = 0; i < capcount; i++)
      {
      fprintf(outfile, "%2dL ", i);
      PCHARSV(stringlist[i], 0, lengths[i], utf, outfile);
      putc('\n', outfile);
      }
    if (stringlist[i] != NULL)
      fprintf(outfile, "string list not terminated by NULL\n");
    PCRE2_SUBSTRING_LIST_FREE(stringlist);
    }
  }

return TRUE;
}



/*************************************************
*               Process a data line              *
*************************************************/

/* The line is in buffer; it will not be empty.

Arguments:  none

Returns:    PR_OK     continue processing next line
            PR_SKIP   skip to a blank line
            PR_ABEND  abort the pcre2test run
*/

static int
process_data(void)
{
PCRE2_SIZE ulen, arg_ulen;
uint32_t gmatched;
uint32_t c, k;
uint32_t g_notempty = 0;
uint8_t *p, *pp, *start_rep;
size_t len, needlen;
void *use_dat_context;
BOOL utf;
BOOL subject_literal;

PCRE2_SIZE *ovector;
uint8_t *ovecsave[2] = { NULL, NULL };
uint32_t oveccount;

#ifdef SUPPORT_PCRE2_8
uint8_t *q8 = NULL;
#endif
#ifdef SUPPORT_PCRE2_16
uint16_t *q16 = NULL;
#endif
#ifdef SUPPORT_PCRE2_32
uint32_t *q32 = NULL;
#endif

subject_literal = (pat_patctl.control2 & CTL2_SUBJECT_LITERAL) != 0;

/* Copy the default context and data control blocks to the active ones. Then
copy from the pattern the controls that can be set in either the pattern or the
data. This allows them to be overridden in the data line. We do not do this for
options because those that are common apply separately to compiling and
matching. */

DATCTXCPY(dat_context, default_dat_context);
memcpy(&dat_datctl, &def_datctl, sizeof(datctl));
dat_datctl.control |= (pat_patctl.control & CTL_ALLPD);
dat_datctl.control2 |= (pat_patctl.control2 & CTL2_ALLPD);
strcpy((char *)dat_datctl.replacement, (char *)pat_patctl.replacement);
if (dat_datctl.jitstack == 0) dat_datctl.jitstack = pat_patctl.jitstack;

if (dat_datctl.substitute_skip == 0)
    dat_datctl.substitute_skip = pat_patctl.substitute_skip;
if (dat_datctl.substitute_stop == 0)
    dat_datctl.substitute_stop = pat_patctl.substitute_stop;

/* Initialize for scanning the data line. */

#ifdef SUPPORT_PCRE2_8
utf = ((((pat_patctl.control & CTL_POSIX) != 0)?
  ((pcre2_real_code_8 *)preg.re_pcre2_code)->overall_options :
  FLD(compiled_code, overall_options)) & PCRE2_UTF) != 0;
#else
utf = (FLD(compiled_code, overall_options) & PCRE2_UTF) != 0;
#endif

start_rep = NULL;
len = strlen((const char *)buffer);
while (len > 0 && isspace(buffer[len-1])) len--;
buffer[len] = 0;
p = buffer;
while (isspace(*p))
  {
  p++;
  len--;
  }

/* Check that the data is well-formed UTF-8 if we're in UTF mode. To create
invalid input to pcre2_match(), you must use \x?? or \x{} sequences. */

if (utf)
  {
  uint8_t *q;
  uint32_t cc;
  int n = 1;
  uint8_t *q_end = p + len;

  for (q = p; n > 0 && *q; q += n) n = utf8_to_ord(q, q_end, &cc);
  if (n <= 0)
    {
    fprintf(outfile, "** Failed: invalid UTF-8 string cannot be used as input "
      "in UTF mode\n");
    return PR_OK;
    }
  }

#ifdef SUPPORT_VALGRIND
/* Mark the dbuffer as addressable but undefined again. */
if (dbuffer != NULL)
  {
  VALGRIND_MAKE_MEM_UNDEFINED(dbuffer, dbuffer_size);
  }
#endif

/* Allocate a buffer to hold the data line; len+1 is an upper bound on
the number of code units that will be needed (though the buffer may have to be
extended if replication is involved). */

needlen = (len+1) * code_unit_size;
if (dbuffer == NULL || needlen >= dbuffer_size)
  {
  while (needlen >= dbuffer_size)
    {
    if (dbuffer_size < SIZE_MAX/2) dbuffer_size *= 2;
      else dbuffer_size = needlen + 1;
    }
  dbuffer = (uint8_t *)realloc(dbuffer, dbuffer_size);
  if (dbuffer == NULL)
    {
    fprintf(stderr, "pcre2test: realloc(%" SIZ_FORM ") failed\n", dbuffer_size);
    exit(1);
    }
  }
SETCASTPTR(q, dbuffer);  /* Sets q8, q16, or q32, as appropriate. */

/* Scan the data line, interpreting data escapes, and put the result into a
buffer of the appropriate width. In UTF mode, input is always UTF-8; otherwise,
in 16- and 32-bit modes, it can be forced to UTF-8 by the utf8_input modifier.
*/

while ((c = *p++) != 0)
  {
  int i = 0;
  size_t replen;
  enum force_encoding encoding = FORCE_NONE;

  /* ] may mark the end of a replicated sequence */

  if (c == ']' && start_rep != NULL)
    {
    long li;
    char *endptr;

    if (*p++ != '{')
      {
      fprintf(outfile, "** Expected '{' after \\[....]\n");
      return PR_OK;
      }

    li = strtol((const char *)p, &endptr, 10);
    if (S32OVERFLOW(li))
      {
      fprintf(outfile, "** Repeat count too large\n");
      return PR_OK;
      }
    i = (int)li;

    p = (uint8_t *)endptr;
    if (*p++ != '}')
      {
      fprintf(outfile, "** Expected '}' after \\[...]{...\n");
      return PR_OK;
      }

    if (i-- <= 0)
      {
      fprintf(outfile, "** Zero or negative repeat not allowed\n");
      return PR_OK;
      }

    replen = CAST8VAR(q) - start_rep;
    if (i > 0 && replen > (SIZE_MAX - needlen) / i)
      {
      fprintf(outfile, "** Expanded content too large\n");
      return PR_OK;
      }
    needlen += replen * i;

    if (needlen >= dbuffer_size)
      {
      size_t qoffset = CAST8VAR(q) - dbuffer;
      size_t rep_offset = start_rep - dbuffer;
      while (needlen >= dbuffer_size)
        {
        if (dbuffer_size < SIZE_MAX/2) dbuffer_size *= 2;
          else dbuffer_size = needlen + 1;
        }
      dbuffer = (uint8_t *)realloc(dbuffer, dbuffer_size);
      if (dbuffer == NULL)
        {
        fprintf(stderr, "pcre2test: realloc(%" SIZ_FORM ") failed\n",
          dbuffer_size);
        exit(1);
        }
      SETCASTPTR(q, dbuffer + qoffset);
      start_rep = dbuffer + rep_offset;
      }

    while (i-- > 0)
      {
      memcpy(CAST8VAR(q), start_rep, replen);
      SETPLUS(q, replen/code_unit_size);
      }

    start_rep = NULL;
    continue;
    }

  /* Handle a non-escaped character. In non-UTF 32-bit mode with utf8_input
  set, do the fudge for setting the top bit. */

  if (c != '\\' || subject_literal)
    {
    uint32_t topbit = 0;
#ifdef SUPPORT_PCRE2_32
    if (test_mode == PCRE32_MODE && c == 0xff && *p != 0)
      {
      topbit = 0x80000000;
      c = *p++;
      }
#endif
    if ((utf || (pat_patctl.control & CTL_UTF8_INPUT) != 0) &&
        HASUTF8EXTRALEN(c))
      {
      GETUTF8INC(c, p);
      }
    c |= topbit;
    }

  /* Handle backslash escapes */

  else switch ((c = *p++))
    {
    case '\\': break;
    case 'a': c = '\a'; break;
    case 'b': c = '\b'; break;
#if defined(EBCDIC) && !EBCDIC_IO
    /* \e is the odd one out since it's not defined in the C standard,
    precisely because of EBCDIC (apparently EBCDIC 'ESC' character isn't
    an exact match to Latin-1 'ESC', hence '\e' isn't necessarily
    supported by EBCDIC compilers). */
    case 'e': c = '\x1b'; break;
#else
    case 'e': c = CHAR_ESC; break;
#endif
    case 'f': c = '\f'; break;
    case 'n': c = '\n'; break;
    case 'r': c = '\r'; break;
    case 't': c = '\t'; break;
    case 'v': c = '\v'; break;

    case '0': case '1': case '2': case '3':
    case '4': case '5': case '6': case '7':
    c -= '0';
    while (i++ < 2 && isdigit(*p) && *p < '8')
      c = c * 8 + (*p++ - '0');
    c = CHAR_OUTPUT(CHAR_INPUT_HEX(c));

    encoding = (utf && c > 255)? FORCE_UTF : FORCE_RAW;
    break;

    case 'o':
    if (*p == '{')
      {
      uint8_t *pt = p;
      c = 0;
      for (pt++; isdigit(*pt) && *pt < '8'; ++i, pt++)
        {
        if (c >= 0x20000000u)
          {
          fprintf(outfile, "** \\o{ escape too large\n");
          return PR_OK;
          }
        else c = c * 8 + (*pt - '0');
        }
      c = CHAR_OUTPUT(CHAR_INPUT_HEX(c));
      if (i == 0 || *pt != '}')
        {
        fprintf(outfile, "** Malformed \\o{ escape\n");
        return PR_OK;
        }
      else p = pt + 1;
      }
    break;

    case 'x':
    c = 0;
    if (*p == '{')
      {
      uint8_t *pt = p;

      /* We used to have "while (isxdigit(*(++pt)))" here, but it fails
      when isxdigit() is a macro that refers to its argument more than
      once. This is banned by the C Standard, but apparently happens in at
      least one macOS environment. */

      for (pt++; isxdigit(*pt); pt++)
        {
        if (++i == 9)
          {
          fprintf(outfile, "** Too many hex digits in \\x{...} item; "
                           "using only the first eight.\n");
          while (isxdigit(*pt)) pt++;
          break;
          }
        else c = c * 16 + (tolower(*pt) - (isdigit(*pt)? '0' : 'a' - 10));
        }
      c = CHAR_OUTPUT(CHAR_INPUT_HEX(c));
      if (i == 0 || *pt != '}')
        {
        fprintf(outfile, "** Malformed \\x{ escape\n");
        return PR_OK;
        }
      else p = pt + 1;
      }
    else
      {
      /* \x without {} always defines just one byte in 8-bit mode. This
      allows UTF-8 characters to be constructed byte by byte, and also allows
      invalid UTF-8 sequences to be made. Just copy the byte in UTF-8 mode.
      Otherwise, pass it down as data. */

      while (i++ < 2 && isxdigit(*p))
        {
        c = c * 16 + (tolower(*p) - (isdigit(*p)? '0' : 'a' - 10));
        p++;
        }
      c = CHAR_OUTPUT(CHAR_INPUT_HEX(c));
#if defined SUPPORT_PCRE2_8
      if (utf && (test_mode == PCRE8_MODE)) encoding = FORCE_RAW;
#endif
      }
    break;

    case 'N':
#ifndef EBCDIC
    if (memcmp(p, "{U+", 3) == 0 && isxdigit(p[3]))
      {
      char *endptr;
      unsigned long uli;

      p += 3;
      errno = 0;
      uli = strtoul((const char *)p, &endptr, 16);
      if (errno == 0 && *endptr == '}' && uli <= UINT32_MAX)
        {
        c = (uint32_t)uli;
        p = (uint8_t *)endptr + 1;
        encoding = FORCE_UTF;
        break;
        }
      }
#endif
    fprintf(outfile, "** Malformed \\N{U+ escape\n");
    return PR_OK;

    case 0:     /* \ followed by EOF allows for an empty line */
    p--;
    continue;

    case '=':   /* \= terminates the data, starts modifiers */
    goto ENDSTRING;

    case '[':   /* \[ introduces a replicated character sequence */
    if (start_rep != NULL)
      {
      fprintf(outfile, "** Nested replication is not supported\n");
      return PR_OK;
      }
    start_rep = CAST8VAR(q);
    continue;

    default:
    if (isalnum(c))
      {
      fprintf(outfile, "** Unrecognized escape sequence \"\\%c\"\n", c);
      return PR_OK;
      }
    }

  /* We now have a character value in c that may be greater than 255.
  Depending of how we got it, the encoding enum could be set to tell
  us how to encode it, otherwise follow the utf modifier. */

#ifdef SUPPORT_PCRE2_8
  if (test_mode == PCRE8_MODE)
    {
    if (encoding == FORCE_RAW || !(utf || encoding == FORCE_UTF))
      {
      if (c > 0xffu)
        {
        fprintf(outfile, "** Character \\x{%x} is greater than 255 "
          "and UTF-8 mode is not enabled.\n", c);
        fprintf(outfile, "** Truncation will probably give the wrong "
          "result.\n");
        }
      *q8++ = (uint8_t)c;
      }
    else
      {
      if (c > 0x7fffffff)
        {
        fprintf(outfile, "** Character \\N{U+%x} is greater than 0x7fffffff "
                         "and therefore cannot be encoded as UTF-8\n", c);
        return PR_OK;
        }
      else if (encoding == FORCE_UTF && c > MAX_UTF_CODE_POINT)
        fprintf(outfile, "** Warning: character \\N{U+%x} is greater than "
                         "0x%x and should not be encoded as UTF-8\n",
                         c, MAX_UTF_CODE_POINT);
      q8 += ord_to_utf8(c, q8);
      }
    }
#endif
#ifdef SUPPORT_PCRE2_16
  if (test_mode == PCRE16_MODE)
    {
    /* Unlike the 8-bit code, there are no forced raw suggestions for the
    16-bit mode, so assume raw unless utf is preferred */

    if (!(encoding == FORCE_UTF || utf))
      {
      if (c > 0xffffu)
        {
        fprintf(outfile, "** Character \\x{%x} is greater than 0xffff "
          "and UTF-16 mode is not enabled.\n", c);
        fprintf(outfile, "** Truncation will probably give the wrong "
          "result.\n");
        }
      *q16++ = (uint16_t)c;
      }
    else
      {
      if (c > MAX_UTF_CODE_POINT)
        {
        fprintf(outfile, "** Failed: character \\N{U+%x} is greater than "
                         "0x%x and therefore cannot be encoded as UTF-16\n",
                c, MAX_UTF_CODE_POINT);
        return PR_OK;
        }
      else if (c >= 0x10000u)
        {
        c -= 0x10000u;
        *q16++ = 0xd800 | (c >> 10);
        *q16++ = 0xdc00 | (c & 0x3ff);
        }
      else
        {
        if (encoding == FORCE_UTF && 0xe000u > c && c >= 0xd800u)
          fprintf(outfile, "** Warning: character \\N{U+%x} is a surrogate "
                           "and should not be encoded as UTF-16\n", c);
        *q16++ = c;
        }
      }
    }
#endif
#ifdef SUPPORT_PCRE2_32
  if (test_mode == PCRE32_MODE)
    {
    if (encoding == FORCE_UTF && c > MAX_UTF_CODE_POINT)
      fprintf(outfile, "** Warning: character \\N{U+%x} is greater than "
                       "0x%x and should not be encoded as UTF-32\n",
                       c, MAX_UTF_CODE_POINT);
    *q32++ = c;
    }
#endif
  }

ENDSTRING:
SET(*q, 0);
len = CASTVAR(uint8_t *, q) - dbuffer;    /* Length in bytes */
ulen = len/code_unit_size;                /* Length in code units */
arg_ulen = ulen;                          /* Value to use in match arg */

/* If the string was terminated by \= we must now interpret modifiers. */

if (p[-1] != 0 && !decode_modifiers(p, CTX_DAT, NULL, &dat_datctl))
  return PR_OK;

/* Setting substitute_{skip,fail} implies a substitute callout. */

if (dat_datctl.substitute_skip != 0 || dat_datctl.substitute_stop != 0)
  dat_datctl.control2 |= CTL2_SUBSTITUTE_CALLOUT;

/* Check for mutually exclusive modifiers. At present, these are all in the
first control word. */

for (k = 0; k < sizeof(exclusive_dat_controls)/sizeof(uint32_t); k++)
  {
  c = dat_datctl.control & exclusive_dat_controls[k];
  if (c != 0 && c != (c & (~c+1)))
    {
    show_controls(c, 0, "** Not allowed together:");
    fprintf(outfile, "\n");
    return PR_OK;
    }
  }

if (dat_datctl.replacement[0] != 0)
  {
  if ((dat_datctl.control2 & CTL2_SUBSTITUTE_CALLOUT) != 0 &&
      (dat_datctl.control & CTL_NULLCONTEXT) != 0)
    {
    fprintf(outfile, "** Replacement callouts are not supported with null_context.\n");
    return PR_OK;
    }

  if ((dat_datctl.control2 & CTL2_SUBSTITUTE_CASE_CALLOUT) != 0 &&
      (dat_datctl.control & CTL_NULLCONTEXT) != 0)
    {
    fprintf(outfile, "** Replacement case callouts are not supported with null_context.\n");
    return PR_OK;
    }

  if ((dat_datctl.control & CTL_ALLCAPTURES) != 0)
    fprintf(outfile, "** Ignored with replacement text: allcaptures\n");
  }

/* Warn for modifiers that are ignored for DFA. */

if ((dat_datctl.control & CTL_DFA) != 0)
  {
  if ((dat_datctl.control & CTL_ALLCAPTURES) != 0)
    fprintf(outfile, "** Ignored for DFA matching: allcaptures\n");
  if ((dat_datctl.control2 & CTL2_HEAPFRAMES_SIZE) != 0)
    fprintf(outfile, "** Ignored for DFA matching: heapframes_size\n");
  }

/* We now have the subject in dbuffer, with len containing the byte length, and
ulen containing the code unit length, with a copy in arg_ulen for use in match
function arguments (this gets changed to PCRE2_ZERO_TERMINATED when the
zero_terminate modifier is present).

Move the data to the end of the buffer so that a read over the end can be
caught by valgrind or other means. If we have explicit valgrind support, mark
the unused start of the buffer unaddressable. If we are using the POSIX
interface, or testing zero-termination, we must include the terminating zero in
the usable data. */

c = code_unit_size * ((((pat_patctl.control & CTL_POSIX) != 0) +
                       ((dat_datctl.control & CTL_ZERO_TERMINATE) != 0))? 1 : 0);
pp = memmove(dbuffer + dbuffer_size - (len + c), dbuffer, len + c);
#ifdef SUPPORT_VALGRIND
VALGRIND_MAKE_MEM_NOACCESS(dbuffer, dbuffer_size - (len + c));
#endif

#if defined(EBCDIC) && !EBCDIC_IO
ascii_to_ebcdic_str(pp, len);
#endif

/* Now pp points to the subject string, but if null_subject was specified, set
it to NULL to test PCRE2's behaviour. */

if ((dat_datctl.control2 & CTL2_NULL_SUBJECT) != 0) pp = NULL;

/* POSIX matching is only possible in 8-bit mode, and it does not support
timing or other fancy features. Some were checked at compile time, but we need
to check the match-time settings here. */

#ifdef SUPPORT_PCRE2_8
if ((pat_patctl.control & CTL_POSIX) != 0)
  {
  int rc;
  int eflags = 0;
  regmatch_t *pmatch = NULL;
  const char *msg = "** Ignored with POSIX interface:";

  if (dat_datctl.cerror[0] != CFORE_UNSET || dat_datctl.cerror[1] != CFORE_UNSET)
    prmsg(&msg, "callout_error");
  if (dat_datctl.cfail[0] != CFORE_UNSET || dat_datctl.cfail[1] != CFORE_UNSET)
    prmsg(&msg, "callout_fail");
  if (dat_datctl.copy_numbers[0] >= 0 || dat_datctl.copy_names[0] != 0)
    prmsg(&msg, "copy");
  if (dat_datctl.get_numbers[0] >= 0 || dat_datctl.get_names[0] != 0)
    prmsg(&msg, "get");
  if (dat_datctl.jitstack != 0) prmsg(&msg, "jitstack");
  if (dat_datctl.offset != 0) prmsg(&msg, "offset");

  if ((dat_datctl.options & ~POSIX_SUPPORTED_MATCH_OPTIONS) != 0)
    {
    fprintf(outfile, "%s", msg);
    show_match_options(dat_datctl.options & ~POSIX_SUPPORTED_MATCH_OPTIONS);
    msg = "";
    }

  if ((dat_datctl.control & ~POSIX_SUPPORTED_MATCH_CONTROLS) != 0 ||
      (dat_datctl.control2 & ~POSIX_SUPPORTED_MATCH_CONTROLS2) != 0)
    {
    show_controls(dat_datctl.control & ~POSIX_SUPPORTED_MATCH_CONTROLS,
                  dat_datctl.control2 & ~POSIX_SUPPORTED_MATCH_CONTROLS2, msg);
    msg = "";
    }

  if (msg[0] == 0) fprintf(outfile, "\n");

  if (dat_datctl.oveccount > 0)
    {
    pmatch = (regmatch_t *)malloc(sizeof(regmatch_t) * dat_datctl.oveccount);
    if (pmatch == NULL)
      {
      fprintf(outfile, "** Failed to get memory for recording matching "
        "information (size set = %du)\n", dat_datctl.oveccount);
      return PR_OK;
      }
    }

  if (dat_datctl.startend[0] != CFORE_UNSET)
    {
    pmatch[0].rm_so = (regoff_t)dat_datctl.startend[0];
    pmatch[0].rm_eo = (dat_datctl.startend[1] != 0)?
      (regoff_t)dat_datctl.startend[1] : (regoff_t)len;
    eflags |= REG_STARTEND;
    }

  if ((dat_datctl.options & PCRE2_NOTBOL) != 0) eflags |= REG_NOTBOL;
  if ((dat_datctl.options & PCRE2_NOTEOL) != 0) eflags |= REG_NOTEOL;
  if ((dat_datctl.options & PCRE2_NOTEMPTY) != 0) eflags |= REG_NOTEMPTY;

  rc = regexec(&preg, (const char *)pp, dat_datctl.oveccount, pmatch, eflags);
  if (rc != 0)
    {
    (void)regerror(rc, &preg, (char *)pbuffer8, pbuffer8_size);
    fprintf(outfile, "No match: POSIX code %d: %s\n", rc, pbuffer8);
    }
  else if ((pat_patctl.control & CTL_POSIX_NOSUB) != 0)
    fprintf(outfile, "Matched with REG_NOSUB\n");
  else if (dat_datctl.oveccount == 0)
    fprintf(outfile, "Matched without capture\n");
  else
    {
    size_t i, j;
    size_t last_printed = (size_t)dat_datctl.oveccount;
    for (i = 0; i < (size_t)dat_datctl.oveccount; i++)
      {
      if (pmatch[i].rm_so >= 0)
        {
        PCRE2_SIZE start = pmatch[i].rm_so;
        PCRE2_SIZE end = pmatch[i].rm_eo;
        for (j = last_printed + 1; j < i; j++)
          fprintf(outfile, "%2d: <unset>\n", (int)j);
        last_printed = i;
        if (start > end)
          {
          start = pmatch[i].rm_eo;
          end = pmatch[i].rm_so;
          fprintf(outfile, "Start of matched string is beyond its end - "
            "displaying from end to start.\n");
          }
        fprintf(outfile, "%2d: ", (int)i);
        PCHARSV(pp, start, end - start, utf, outfile);
        fprintf(outfile, "\n");

        if ((i == 0 && (dat_datctl.control & CTL_AFTERTEXT) != 0) ||
            (dat_datctl.control & CTL_ALLAFTERTEXT) != 0)
          {
          fprintf(outfile, "%2d+ ", (int)i);
          /* Note: don't use the start/end variables here because we want to
          show the text from what is reported as the end. */
          PCHARSV(pp, pmatch[i].rm_eo, len - pmatch[i].rm_eo, utf, outfile);
          fprintf(outfile, "\n"); }
        }
      }
    }
  free(pmatch);
  return PR_OK;
  }
#endif  /* SUPPORT_PCRE2_8 */

 /* Handle matching via the native interface. Check for consistency of
modifiers. */

if (dat_datctl.startend[0] != CFORE_UNSET)
  fprintf(outfile, "** \\=posix_startend ignored for non-POSIX matching\n");

/* ALLUSEDTEXT is not supported with JIT, but JIT is not used with DFA
matching, even if the JIT compiler was used. */

if ((dat_datctl.control & (CTL_ALLUSEDTEXT|CTL_DFA)) == CTL_ALLUSEDTEXT &&
    FLD(compiled_code, executable_jit) != NULL)
  {
  fprintf(outfile, "** Showing all consulted text is not supported by JIT: ignored\n");
  dat_datctl.control &= ~CTL_ALLUSEDTEXT;
  }

/* Handle passing the subject as zero-terminated. */

if ((dat_datctl.control & CTL_ZERO_TERMINATE) != 0)
  arg_ulen = PCRE2_ZERO_TERMINATED;

/* The nullcontext modifier is used to test calling pcre2_[jit_]match() with a
NULL context. */

use_dat_context = ((dat_datctl.control & CTL_NULLCONTEXT) != 0)?
  NULL : PTR(dat_context);

/* Enable display of malloc/free if wanted. We can do this only if either the
pattern or the subject is processed with a context. */

show_memory = (dat_datctl.control & CTL_MEMORY) != 0;

if (show_memory &&
    (pat_patctl.control & dat_datctl.control & CTL_NULLCONTEXT) != 0)
  fprintf(outfile, "** \\=memory requires either a pattern or a subject "
    "context: ignored\n");

/* Create and assign a JIT stack if requested. */

if (dat_datctl.jitstack != 0)
  {
  if (dat_datctl.jitstack != jit_stack_size)
    {
    PCRE2_JIT_STACK_FREE(jit_stack);
    PCRE2_JIT_STACK_CREATE(jit_stack, 1, dat_datctl.jitstack * 1024, NULL);
    jit_stack_size = dat_datctl.jitstack;
    }
  PCRE2_JIT_STACK_ASSIGN(dat_context, jit_callback, jit_stack);
  }

/* Or de-assign */

else if (jit_stack != NULL)
  {
  PCRE2_JIT_STACK_ASSIGN(dat_context, NULL, NULL);
  PCRE2_JIT_STACK_FREE(jit_stack);
  jit_stack = NULL;
  jit_stack_size = 0;
  }

/* When no JIT stack is assigned, we must ensure that there is a JIT callback
if we want to verify that JIT was actually used. */

if ((pat_patctl.control & CTL_JITVERIFY) != 0 && jit_stack == NULL)
   {
   PCRE2_JIT_STACK_ASSIGN(dat_context, jit_callback, NULL);
   }

/* Adjust match_data according to size of offsets required. A size of zero
causes a new match data block to be obtained that exactly fits the pattern. */

if (dat_datctl.oveccount == 0)
  {
  PCRE2_MATCH_DATA_FREE(match_data);
  PCRE2_MATCH_DATA_CREATE_FROM_PATTERN(match_data, compiled_code,
    general_context);
  PCRE2_GET_OVECTOR_COUNT(max_oveccount, match_data);
  }
else if (dat_datctl.oveccount <= max_oveccount)
  {
  SETFLD(match_data, oveccount, dat_datctl.oveccount);
  }
else
  {
  max_oveccount = dat_datctl.oveccount;
  PCRE2_MATCH_DATA_FREE(match_data);
  PCRE2_MATCH_DATA_CREATE(match_data, max_oveccount, general_context);
  }

if (CASTVAR(void *, match_data) == NULL)
  {
  fprintf(outfile, "** Failed to get memory for recording matching "
    "information (size requested: %d)\n", dat_datctl.oveccount);
  max_oveccount = 0;
  return PR_OK;
  }

ovector = FLD(match_data, ovector);
PCRE2_GET_OVECTOR_COUNT(oveccount, match_data);

/* Helper to clear any cached heap frames from the match_data. */

#define CLEAR_HEAP_FRAMES() \
  do { \
     void *heapframes = (void *)(FLD(match_data, heapframes)); \
     void *memory_data = FLD(match_data, memctl.memory_data); \
     FLD(match_data, memctl.free(heapframes, memory_data)); \
     SETFLD(match_data,heapframes,NULL); \
     SETFLD(match_data,heapframes_size,0); \
     } \
  while (0)

/* Replacement processing is ignored for DFA matching. */

if (dat_datctl.replacement[0] != 0 && (dat_datctl.control & CTL_DFA) != 0)
  {
  fprintf(outfile, "** Ignored for DFA matching: replace\n");
  dat_datctl.replacement[0] = 0;
  }

/* If a replacement string is provided, call pcre2_substitute() instead of or
after one of the matching functions. First we have to convert the replacement
string to the appropriate width. */

if (dat_datctl.replacement[0] != 0)
  {
  int rc;
  uint8_t *pr;
  uint8_t rbuffer[REPLACE_BUFFSIZE];
  uint8_t nbuffer[REPLACE_BUFFSIZE];
  uint8_t *rbptr;
  uint32_t xoptions;
  uint32_t emoption;  /* External match option */
  PCRE2_SIZE j, rlen, nsize, nsize_input, erroroffset;
  BOOL badutf = FALSE;

#ifdef SUPPORT_PCRE2_8
  uint8_t *r8 = NULL;
#endif
#ifdef SUPPORT_PCRE2_16
  uint16_t *r16 = NULL;
#endif
#ifdef SUPPORT_PCRE2_32
  uint32_t *r32 = NULL;
#endif

  /* Fill the ovector with junk to detect elements that do not get set
  when they should be (relevant only when "allvector" is specified). */

  for (j = 0; j < 2*oveccount; j++) ovector[j] = JUNK_OFFSET;

  if (timeitm)
    fprintf(outfile, "** Timing is not supported with replace: ignored\n");

  if ((dat_datctl.control & CTL_ALTGLOBAL) != 0)
    fprintf(outfile, "** Altglobal is not supported with replace: ignored\n");

  /* Check for a test that does substitution after an initial external match.
  If this is set, we run the external match, but leave the interpretation of
  its output to pcre2_substitute(). */

  emoption = ((dat_datctl.control2 & CTL2_SUBSTITUTE_MATCHED) == 0)? 0 :
    PCRE2_SUBSTITUTE_MATCHED;

  if (emoption != 0)
    {
    if ((pat_patctl.control & CTL_JITFAST) != 0)
      {
      PCRE2_JIT_MATCH(rc, compiled_code, pp, arg_ulen, dat_datctl.offset,
        dat_datctl.options, match_data, use_dat_context);
      }
    else
      {
      PCRE2_MATCH(rc, compiled_code, pp, arg_ulen, dat_datctl.offset,
        dat_datctl.options, match_data, use_dat_context);
      }
    }

  xoptions = emoption |
             (((dat_datctl.control & CTL_GLOBAL) == 0)? 0 :
                PCRE2_SUBSTITUTE_GLOBAL) |
             (((dat_datctl.control2 & CTL2_SUBSTITUTE_EXTENDED) == 0)? 0 :
                PCRE2_SUBSTITUTE_EXTENDED) |
             (((dat_datctl.control2 & CTL2_SUBSTITUTE_LITERAL) == 0)? 0 :
                PCRE2_SUBSTITUTE_LITERAL) |
             (((dat_datctl.control2 & CTL2_SUBSTITUTE_OVERFLOW_LENGTH) == 0)? 0 :
                PCRE2_SUBSTITUTE_OVERFLOW_LENGTH) |
             (((dat_datctl.control2 & CTL2_SUBSTITUTE_REPLACEMENT_ONLY) == 0)? 0 :
                PCRE2_SUBSTITUTE_REPLACEMENT_ONLY) |
             (((dat_datctl.control2 & CTL2_SUBSTITUTE_UNKNOWN_UNSET) == 0)? 0 :
                PCRE2_SUBSTITUTE_UNKNOWN_UNSET) |
             (((dat_datctl.control2 & CTL2_SUBSTITUTE_UNSET_EMPTY) == 0)? 0 :
                PCRE2_SUBSTITUTE_UNSET_EMPTY);

  SETCASTPTR(r, rbuffer);  /* Sets r8, r16, or r32, as appropriate. */
  pr = dat_datctl.replacement;

  /* If the replacement starts with '[<number>]' we interpret that as length
  value for the replacement buffer. */

  nsize = REPLACE_BUFFSIZE/code_unit_size;
  if (*pr == '[')
    {
    PCRE2_SIZE n = 0;
    while ((c = *(++pr)) >= '0' && c <= '9') n = n * 10 + (c - '0');
    if (*pr++ != ']')
      {
      fprintf(outfile, "Bad buffer size in replacement string\n");
      return PR_OK;
      }
    if (n > nsize)
      {
      fprintf(outfile, "Replacement buffer setting (%" SIZ_FORM ") is too "
        "large (max %" SIZ_FORM ")\n", n, nsize);
      return PR_OK;
      }
    nsize = n;
    }

  /* Now copy the replacement string to a buffer of the appropriate width. No
  escape processing is done for replacements. In UTF mode, check for an invalid
  UTF-8 input string, and if it is invalid, just copy its code units without
  UTF interpretation. This provides a means of checking that an invalid string
  is detected. Otherwise, UTF-8 can be used to include wide characters in a
  replacement. */

  if (utf) badutf = valid_utf(pr, strlen((const char *)pr), &erroroffset);

  /* Not UTF or invalid UTF-8: just copy the code units. */

  if (!utf || badutf)
    {
    while ((c = *pr++) != 0)
      {
#if defined(EBCDIC) && !EBCDIC_IO
      c = ascii_to_ebcdic(c);
#endif
#ifdef SUPPORT_PCRE2_8
      if (test_mode == PCRE8_MODE) *r8++ = c;
#endif
#ifdef SUPPORT_PCRE2_16
      if (test_mode == PCRE16_MODE) *r16++ = c;
#endif
#ifdef SUPPORT_PCRE2_32
      if (test_mode == PCRE32_MODE) *r32++ = c;
#endif
      }
    }

  /* Valid UTF-8 replacement string */

  else while ((c = *pr++) != 0)
    {
    if (HASUTF8EXTRALEN(c)) { GETUTF8INC(c, pr); }

#ifdef SUPPORT_PCRE2_8
    if (test_mode == PCRE8_MODE) r8 += ord_to_utf8(c, r8);
#endif

#ifdef SUPPORT_PCRE2_16
    if (test_mode == PCRE16_MODE)
      {
      if (c >= 0x10000u)
        {
        c-= 0x10000u;
        *r16++ = 0xd800 | (c >> 10);
        *r16++ = 0xdc00 | (c & 0x3ff);
        }
      else *r16++ = c;
      }
#endif

#ifdef SUPPORT_PCRE2_32
    if (test_mode == PCRE32_MODE) *r32++ = c;
#endif
    }

  SET(*r, 0);
  if ((dat_datctl.control & CTL_ZERO_TERMINATE) != 0)
    rlen = PCRE2_ZERO_TERMINATED;
  else
    rlen = (CASTVAR(uint8_t *, r) - rbuffer)/code_unit_size;

  if ((dat_datctl.control2 & CTL2_SUBSTITUTE_CALLOUT) != 0)
    {
    PCRE2_SET_SUBSTITUTE_CALLOUT(dat_context, substitute_callout_function, NULL);
    }
  else
    {
    PCRE2_SET_SUBSTITUTE_CALLOUT(dat_context, NULL, NULL);  /* No callout */
    }

  if ((dat_datctl.control2 & CTL2_SUBSTITUTE_CASE_CALLOUT) != 0)
    {
    PCRE2_SET_SUBSTITUTE_CASE_CALLOUT(dat_context, substitute_case_callout_function, NULL);
    }
  else
    {
    PCRE2_SET_SUBSTITUTE_CASE_CALLOUT_NULL(dat_context);  /* No callout */
    }

  /* There is a special option to set the replacement to NULL in order to test
  that case. */

  rbptr = ((dat_datctl.control2 & CTL2_NULL_REPLACEMENT) == 0)? rbuffer : NULL;

  if (malloc_testing) CLEAR_HEAP_FRAMES();
  mallocs_called = 0;
  nsize_input = nsize;
  PCRE2_SUBSTITUTE(rc, compiled_code, pp, arg_ulen, dat_datctl.offset,
    dat_datctl.options|xoptions, match_data, use_dat_context,
    rbptr, rlen, nbuffer, &nsize);

  /* For malloc testing, we repeat the substitution. */

  if (malloc_testing && (dat_datctl.control2 & CTL2_SUBSTITUTE_CALLOUT) == 0)
    {
    for (int i = 0, target_mallocs = mallocs_called; i <= target_mallocs; i++)
      {
      CLEAR_HEAP_FRAMES();

      mallocs_until_failure = i;
      nsize = nsize_input;
      PCRE2_SUBSTITUTE(rc, compiled_code, pp, arg_ulen, dat_datctl.offset,
        dat_datctl.options|xoptions, match_data, use_dat_context,
        rbptr, rlen, nbuffer, &nsize);
      mallocs_until_failure = INT_MAX;

      if (i < target_mallocs && rc != PCRE2_ERROR_NOMEMORY)
        {
        fprintf(outfile, "** malloc() Substitution test did not fail as expected (%d)\n",
                rc);
        return PR_ABEND;
        }
      }
    }

  if (rc < 0)
    {
    fprintf(outfile, "Failed: error %d", rc);
    if (rc != PCRE2_ERROR_NOMEMORY && nsize != PCRE2_UNSET)
      fprintf(outfile, " at offset %ld in replacement", (long int)nsize);
    fprintf(outfile, ": ");
    if (!print_error_message(rc, "", "")) return PR_ABEND;
    if (rc == PCRE2_ERROR_NOMEMORY &&
        (xoptions & PCRE2_SUBSTITUTE_OVERFLOW_LENGTH) != 0)
      fprintf(outfile, ": %ld code units are needed", (long int)nsize);

    if (rc != PCRE2_ERROR_NOMEMORY && nsize != PCRE2_UNSET)
      {
      PCRE2_SIZE full_rlen = (rlen != PCRE2_ZERO_TERMINATED)? rlen :
          STRLEN(rbptr);

      fprintf(outfile, "\n        here: ");
      if (nsize > 0)
        {
        PTRUNCV(rbptr, full_rlen, nsize, TRUE, utf, outfile);
        fprintf(outfile, " ");
        }
      fprintf(outfile, "|<--|");
      if (nsize < full_rlen)
        {
        fprintf(outfile, " ");
        PTRUNCV(rbptr, full_rlen, nsize, FALSE, utf, outfile);
        }
      }
    }
  else
    {
    fprintf(outfile, "%2d: ", rc);
    PCHARSV(nbuffer, 0, nsize, utf, outfile);
    }

  fprintf(outfile, "\n");
  show_memory = FALSE;

  /* Show final ovector contents and resulting heapframe size if requested. */

  if ((dat_datctl.control2 & CTL2_ALLVECTOR) != 0)
    show_ovector(ovector, oveccount);

  if ((dat_datctl.control2 & CTL2_HEAPFRAMES_SIZE) != 0 &&
      (dat_datctl.control & CTL_DFA) == 0)
    show_heapframes_size();

  return PR_OK;
  }   /* End of substitution handling */

/* When a replacement string is not provided, run a loop for global matching
with one of the basic matching functions. */

for (gmatched = 0;; gmatched++)
  {
  PCRE2_SIZE j;
  int capcount;

  /* Fill the ovector with junk to detect elements that do not get set
  when they should be. */

  for (j = 0; j < 2*oveccount; j++) ovector[j] = JUNK_OFFSET;

  /* When matching is via pcre2_match(), we will detect the use of JIT via the
  stack callback function. */

  jit_was_used = (pat_patctl.control & CTL_JITFAST) != 0;

  /* Do timing if required. */

  if (timeitm > 0)
    {
    int i;
    clock_t start_time, time_taken;

    if ((dat_datctl.control & CTL_DFA) != 0)
      {
      if ((dat_datctl.options & PCRE2_DFA_RESTART) != 0)
        {
        fprintf(outfile, "Timing DFA restarts is not supported\n");
        return PR_OK;
        }
      if (dfa_workspace == NULL)
        dfa_workspace = (int *)malloc(DFA_WS_DIMENSION*sizeof(int));
      start_time = clock();
      for (i = 0; i < timeitm; i++)
        {
        PCRE2_DFA_MATCH(capcount, compiled_code, pp, arg_ulen,
          dat_datctl.offset, dat_datctl.options | g_notempty, match_data,
          use_dat_context, dfa_workspace, DFA_WS_DIMENSION);
        }
      }

    else if ((pat_patctl.control & CTL_JITFAST) != 0)
      {
      start_time = clock();
      for (i = 0; i < timeitm; i++)
        {
        PCRE2_JIT_MATCH(capcount, compiled_code, pp, arg_ulen,
          dat_datctl.offset, dat_datctl.options | g_notempty, match_data,
          use_dat_context);
        }
      }

    else
      {
      start_time = clock();
      for (i = 0; i < timeitm; i++)
        {
        PCRE2_MATCH(capcount, compiled_code, pp, arg_ulen,
          dat_datctl.offset, dat_datctl.options | g_notempty, match_data,
          use_dat_context);
        }
      }
    total_match_time += (time_taken = clock() - start_time);
    fprintf(outfile, "Match time %7.4f microseconds\n",
      ((1000000 / CLOCKS_PER_SEC) * (double)time_taken) / timeitm);
    }

  /* Find the heap, match and depth limits if requested. The depth and heap
  limits are not relevant for JIT. The return from check_match_limit() is the
  return from the final call to pcre2_match() or pcre2_dfa_match(). */

  if ((dat_datctl.control & (CTL_FINDLIMITS|CTL_FINDLIMITS_NOHEAP)) != 0)
    {
    capcount = 0;  /* This stops compiler warnings */
    (void)capcount;

    if ((dat_datctl.control & CTL_FINDLIMITS_NOHEAP) == 0 &&
        (FLD(compiled_code, executable_jit) == NULL ||
          (dat_datctl.options & PCRE2_NO_JIT) != 0))
      {
      (void)check_match_limit(pp, arg_ulen, PCRE2_ERROR_HEAPLIMIT, "heap");
      }

    capcount = check_match_limit(pp, arg_ulen, PCRE2_ERROR_MATCHLIMIT,
      "match");

    if (FLD(compiled_code, executable_jit) == NULL ||
        (dat_datctl.options & PCRE2_NO_JIT) != 0 ||
        (dat_datctl.control & CTL_DFA) != 0)
      {
      capcount = check_match_limit(pp, arg_ulen, PCRE2_ERROR_DEPTHLIMIT,
        "depth");
      }

    if (capcount == 0)
      {
      fprintf(outfile, "Matched, but offsets vector is too small to show all matches\n");
      capcount = dat_datctl.oveccount;
      }
    }

  /* Otherwise just run a single match, setting up a callout if required (the
  default). The pattern remains in pbuffer8/16/32 after compilation, for use
  by callouts. */

  else
    {
    if ((dat_datctl.control & CTL_CALLOUT_NONE) == 0)
      {
      PCRE2_SET_CALLOUT(dat_context, callout_function,
        (void *)(&dat_datctl.callout_data));
      first_callout = TRUE;
      last_callout_mark = NULL;
      callout_count = 0;
      }
    else
      {
      PCRE2_SET_CALLOUT(dat_context, NULL, NULL);  /* No callout */
      }

    /* Run a single DFA or NFA match. */

    if (malloc_testing) CLEAR_HEAP_FRAMES();
    mallocs_called = 0;
    if ((dat_datctl.control & CTL_DFA) != 0)
      {
      if (dfa_workspace == NULL)
        dfa_workspace = (int *)malloc(DFA_WS_DIMENSION*sizeof(int));
      if (dfa_matched++ == 0)
        dfa_workspace[0] = -1;  /* To catch bad restart */
      PCRE2_DFA_MATCH(capcount, compiled_code, pp, arg_ulen,
        dat_datctl.offset, dat_datctl.options | g_notempty, match_data,
        use_dat_context, dfa_workspace, DFA_WS_DIMENSION);
      if (capcount == 0)
        {
        fprintf(outfile, "Matched, but offsets vector is too small to show all matches\n");
        capcount = dat_datctl.oveccount;
        }
      }
    else
      {
      if ((pat_patctl.control & CTL_JITFAST) != 0)
        PCRE2_JIT_MATCH(capcount, compiled_code, pp, arg_ulen, dat_datctl.offset,
          dat_datctl.options | g_notempty, match_data, use_dat_context);
      else
        PCRE2_MATCH(capcount, compiled_code, pp, arg_ulen, dat_datctl.offset,
          dat_datctl.options | g_notempty, match_data, use_dat_context);
      if (capcount == 0)
        {
        fprintf(outfile, "Matched, but too many substrings\n");
        capcount = dat_datctl.oveccount;
        }
      }

    /* For malloc testing, we repeat the matching. */

    if (malloc_testing && (dat_datctl.control & CTL_CALLOUT_NONE) != 0)
      {
      for (int i = 0, target_mallocs = mallocs_called; i <= target_mallocs; i++)
        {
        CLEAR_HEAP_FRAMES();

        mallocs_until_failure = i;

        if ((dat_datctl.control & CTL_DFA) != 0)
          {
          if (dfa_matched++ == 0)
            dfa_workspace[0] = -1;  /* To catch bad restart */
          PCRE2_DFA_MATCH(capcount, compiled_code, pp, arg_ulen,
            dat_datctl.offset, dat_datctl.options | g_notempty, match_data,
            use_dat_context, dfa_workspace, DFA_WS_DIMENSION);
          }
        else
          {
          if ((pat_patctl.control & CTL_JITFAST) != 0)
            PCRE2_JIT_MATCH(capcount, compiled_code, pp, arg_ulen, dat_datctl.offset,
              dat_datctl.options | g_notempty, match_data, use_dat_context);
          else
            PCRE2_MATCH(capcount, compiled_code, pp, arg_ulen, dat_datctl.offset,
              dat_datctl.options | g_notempty, match_data, use_dat_context);
          }

        mallocs_until_failure = INT_MAX;

        if (capcount == 0)
          capcount = dat_datctl.oveccount;

        if (i < target_mallocs && capcount != PCRE2_ERROR_NOMEMORY)
          {
          fprintf(outfile, "** malloc() match test did not fail as expected (%d)\n",
                  capcount);
          return PR_ABEND;
          }
        }
      }
    }

  /* Verify that it's safe to call pcre2_next_match with rc < 0. */

  if (capcount < 0 && (dat_datctl.control & CTL_ANYGLOB) != 0)
    {
      BOOL rc_nextmatch;
      PCRE2_SIZE tmp_offset = 0xcd;
      uint32_t tmp_options = 0xcd;
      PCRE2_NEXT_MATCH(rc_nextmatch, match_data, &tmp_offset, &tmp_options);
      if (rc_nextmatch || tmp_offset != 0xcd || tmp_options != 0xcd)
        {
        fprintf(outfile, "** unexpected pcre2_next_match() for rc < 0\n");
        return PR_ABEND;
        }
    }

  /* The result of the match is now in capcount. First handle a successful
  match. If pp was forced to be NULL (to test NULL handling) it will have been
  treated as an empty string if the length was zero. So re-create that for
  outputting. Don't just point to "" because that leads to a "loss of const"
  warning. */

  if (capcount >= 0)
    {
    if (pp == NULL)
      {
#ifdef SUPPORT_VALGRIND
      /* Mark the start of dbuffer addressable again. */
      VALGRIND_MAKE_MEM_UNDEFINED(dbuffer, 1);
#endif
      pp = dbuffer;
      pp[0] = 0;
      }

    if ((unsigned)capcount > oveccount)   /* Check for lunatic return value */
      {
      fprintf(outfile,
        "** PCRE2 error: returned count %d is too big for ovector count %d\n",
        capcount, oveccount);
      return PR_ABEND;
      }

    /* If PCRE2_COPY_MATCHED_SUBJECT was set, check that things are as they
    should be, but not for fast JIT, where it isn't supported. */

    if ((dat_datctl.options & PCRE2_COPY_MATCHED_SUBJECT) != 0 &&
        (pat_patctl.control & CTL_JITFAST) == 0)
      {
      if ((FLD(match_data, flags) & PCRE2_MD_COPIED_SUBJECT) == 0)
        fprintf(outfile,
          "** PCRE2 error: flag not set after copy_matched_subject\n");

      if (CASTFLD(const void *, match_data, subject) == pp)
        fprintf(outfile,
          "** PCRE2 error: copy_matched_subject has not copied\n");

      if (memcmp(CASTFLD(const void *, match_data, subject), pp, ulen) != 0)
        fprintf(outfile,
          "** PCRE2 error: copy_matched_subject mismatch\n");
      }

    /* If this is not the first time round a global loop, check that the
    returned string has advanced.

    There is one known case where this doesn't happen: when you have a
    "badly-behaved" pattern which uses \K in a lookaround, and breaks the core
    sanity rule that start_offset <= ovector[0] <= ovector[1]. An example would
    be /(?<=\Ka)/g matching "aaa".
      * first attempt, start_offset=0: ovector[0]=0, ovector[1]=1
      * second attempt, start_offset=1: ovector[0]=0, ovector[1]=1

    You can see that even though we *always* ensure that start_offset advances,
    this doesn't guarantee to avoid duplicate matches.

    The pcre2test behaviour is to return all the matches found, except in the
    case where two adjacent matches are an exact duplicate. */

    if (gmatched > 0 &&
        !(dat_datctl.offset <= ovector[0] && ovector[0] <= ovector[1]) &&
        pp + code_unit_size * ovector[0] == ovecsave[0] &&
        pp + code_unit_size * ovector[1] == ovecsave[1])
      {
      fprintf(outfile, "global repeat returned the same match as previous\n");
      goto NEXT_MATCH;
      }

    /* Outside of this exceptional case, we check that either we have a
    "badly-behaved" match (note that not all badly-behaved matches are caught
    above, only *duplicate* ones); or else in the well-behaved case the match
    must make progress.

    "Progress" is measured as ovector[1] strictly advancing, or, an empty match
    after a non-empty match. */

    if (gmatched > 0 &&
        (dat_datctl.offset <= ovector[0] && ovector[0] <= ovector[1]) &&
        !(pp + code_unit_size * ovector[1] > ovecsave[1] ||
          (ovector[1] == ovector[0] && ovecsave[1] != ovecsave[0] &&
           pp + code_unit_size * ovector[1] == ovecsave[1])))
      {
      fprintf(outfile,
        "** PCRE2 error: global repeat did not make progress\n");
      return PR_ABEND;
      }

    ovecsave[0] = pp + code_unit_size * ovector[0];
    ovecsave[1] = pp + code_unit_size * ovector[1];

    /* "allcaptures" requests showing of all captures in the pattern, to check
    unset ones at the end. It may be set on the pattern or the data. Implement
    by setting capcount to the maximum. This is not relevant for DFA matching,
    so ignore it (warning given above). */

    if ((dat_datctl.control & (CTL_ALLCAPTURES|CTL_DFA)) == CTL_ALLCAPTURES)
      {
      capcount = maxcapcount + 1;   /* Allow for full match */
      if (capcount > (int)oveccount) capcount = oveccount;
      }

    /* "allvector" request showing the entire ovector. */

    if ((dat_datctl.control2 & CTL2_ALLVECTOR) != 0) capcount = oveccount;

    /* Output the captured substrings. Note that, for the matched string,
    the use of \K in an assertion can make the start later than the end. */

    for (int i = 0; i < 2*capcount; i += 2)
      {
      PCRE2_SIZE lleft, lmiddle, lright;
      PCRE2_SIZE start = ovector[i];
      PCRE2_SIZE end = ovector[i+1];

      if (start > end)
        {
        start = ovector[i+1];
        end = ovector[i];
        fprintf(outfile, "Start of matched string is beyond its end - "
          "displaying from end to start.\n");
        }

      fprintf(outfile, "%2d: ", i/2);

      /* Check for an unset group */

      if (start == PCRE2_UNSET && end == PCRE2_UNSET)
        {
        fprintf(outfile, "<unset>\n");
        continue;
        }

      /* Check for silly offsets, in particular, values that have not been
      set when they should have been. However, if we are past the end of the
      captures for this pattern ("allvector" causes this), or if we are DFA
      matching, it isn't an error if the entry is unchanged. */

      if (start > ulen || end > ulen)
        {
        if (((dat_datctl.control & CTL_DFA) != 0 ||
              i >= (int)(2*maxcapcount + 2)) &&
            start == JUNK_OFFSET && end == JUNK_OFFSET)
          fprintf(outfile, "<unchanged>\n");
        else
          fprintf(outfile, "ERROR: bad value(s) for offset(s): 0x%lx 0x%lx\n",
            (unsigned long int)start, (unsigned long int)end);
        continue;
        }

      /* When JIT is not being used, ALLUSEDTEXT may be set. (It if is set with
      JIT, it is disabled above, with a comment.) When the match is done by the
      interpreter, leftchar and rightchar are available, and if ALLUSEDTEXT is
      set, and if the leftmost consulted character is before the start of the
      match or the rightmost consulted character is past the end of the match,
      we want to show all consulted characters for the main matched string, and
      indicate which were lookarounds. */

      if (i == 0)
        {
        BOOL showallused;
        PCRE2_SIZE leftchar, rightchar;

        if ((dat_datctl.control & CTL_ALLUSEDTEXT) != 0)
          {
          leftchar = FLD(match_data, leftchar);
          rightchar = FLD(match_data, rightchar);
          showallused = i == 0 && (leftchar < start || rightchar > end);
          }
        else showallused = FALSE;

        if (showallused)
          {
          PCHARS(lleft, pp, leftchar, start - leftchar, utf, outfile);
          PCHARS(lmiddle, pp, start, end - start, utf, outfile);
          PCHARS(lright, pp, end, rightchar - end, utf, outfile);
          if ((pat_patctl.control & CTL_JITVERIFY) != 0 && jit_was_used)
            fprintf(outfile, " (JIT)");
          fprintf(outfile, "\n    ");
          for (j = 0; j < lleft; j++) fprintf(outfile, "<");
          for (j = 0; j < lmiddle; j++) fprintf(outfile, " ");
          for (j = 0; j < lright; j++) fprintf(outfile, ">");
          }

        /* When a pattern contains \K, the start of match position may be
        different to the start of the matched string. When this is the case,
        show it when requested. */

        else if ((dat_datctl.control & CTL_STARTCHAR) != 0)
          {
          PCRE2_SIZE startchar;
          PCRE2_GET_STARTCHAR(startchar, match_data);
          PCHARS(lleft, pp, startchar, start - startchar, utf, outfile);
          PCHARSV(pp, start, end - start, utf, outfile);
          if ((pat_patctl.control & CTL_JITVERIFY) != 0 && jit_was_used)
            fprintf(outfile, " (JIT)");
          if (startchar != start)
            {
            fprintf(outfile, "\n    ");
            for (j = 0; j < lleft; j++) fprintf(outfile, "^");
            }
          }

        /* Otherwise, just show the matched string. */

        else
          {
          PCHARSV(pp, start, end - start, utf, outfile);
          if ((pat_patctl.control & CTL_JITVERIFY) != 0 && jit_was_used)
            fprintf(outfile, " (JIT)");
          }
        }

      /* Not the main matched string. Just show it unadorned. */

      else
        {
        PCHARSV(pp, start, end - start, utf, outfile);
        }

      fprintf(outfile, "\n");

      /* Note: don't use the start/end variables here because we want to
      show the text from what is reported as the end. */

      if ((dat_datctl.control & CTL_ALLAFTERTEXT) != 0 ||
          (i == 0 && (dat_datctl.control & CTL_AFTERTEXT) != 0))
        {
        fprintf(outfile, "%2d+ ", i/2);
        PCHARSV(pp, ovector[i+1], ulen - ovector[i+1], utf, outfile);
        fprintf(outfile, "\n");
        }
      }

    /* Output (*MARK) data if requested */

    if ((dat_datctl.control & CTL_MARK) != 0 &&
         TESTFLD(match_data, mark, !=, NULL))
      {
      fprintf(outfile, "MK: ");
      PCHARSV(CASTFLD(const void *, match_data, mark), -1, -1, utf, outfile);
      fprintf(outfile, "\n");
      }

    /* Process copy/get strings */

    if (!copy_and_get(utf, capcount)) return PR_ABEND;

    }    /* End of handling a successful match */

  /* There was a partial match. The value of ovector[0] is the bumpalong point,
  that is, startchar, not any \K point that might have been passed. When JIT is
  not in use, "allusedtext" may be set, in which case we indicate the leftmost
  consulted character. */

  else if (capcount == PCRE2_ERROR_PARTIAL)
    {
    PCRE2_SIZE leftchar;
    int backlength;
    int rubriclength = 0;

    if ((dat_datctl.control & CTL_ALLUSEDTEXT) != 0)
      {
      leftchar = FLD(match_data, leftchar);
      }
    else leftchar = ovector[0];

    fprintf(outfile, "Partial match");
    if ((dat_datctl.control & CTL_MARK) != 0 &&
         TESTFLD(match_data, mark, !=, NULL))
      {
      fprintf(outfile, ", mark=");
      PCHARS(rubriclength, CASTFLD(const void *, match_data, mark), -1, -1, utf,
        outfile);
      rubriclength += 7;
      }
    fprintf(outfile, ": ");
    rubriclength += 15;

    PCHARS(backlength, pp, leftchar, ovector[0] - leftchar, utf, outfile);
    PCHARSV(pp, ovector[0], ovector[1] - ovector[0], utf, outfile);

    if ((pat_patctl.control & CTL_JITVERIFY) != 0 && jit_was_used)
      fprintf(outfile, " (JIT)");
    fprintf(outfile, "\n");

    if (backlength != 0)
      {
      for (int i = 0; i < rubriclength; i++) fprintf(outfile, " ");
      for (int i = 0; i < backlength; i++) fprintf(outfile, "<");
      fprintf(outfile, "\n");
      }

    if (ulen != ovector[1])
      fprintf(outfile, "** ovector[1] is not equal to the subject length: "
        "%ld != %ld\n", (unsigned long int)ovector[1], (unsigned long int)ulen);

    /* Process copy/get strings */

    if (!copy_and_get(utf, 1)) return PR_ABEND;

    /* "allvector" outputs the entire vector */

    if ((dat_datctl.control2 & CTL2_ALLVECTOR) != 0)
      show_ovector(ovector, oveccount);

    break;  /* Out of the /g loop */
    }       /* End of handling partial match */

  /* A "normal" match failure. There will be a negative error number in
  capcount. */

  else
    {
    switch(capcount)
      {
      case PCRE2_ERROR_NOMATCH:
      if (gmatched == 0)
        {
        fprintf(outfile, "No match");
        if ((dat_datctl.control & CTL_MARK) != 0 &&
             TESTFLD(match_data, mark, !=, NULL))
          {
          fprintf(outfile, ", mark = ");
          PCHARSV(CASTFLD(const void *, match_data, mark), -1, -1, utf, outfile);
          }
        if ((pat_patctl.control & CTL_JITVERIFY) != 0 && jit_was_used)
          fprintf(outfile, " (JIT)");
        fprintf(outfile, "\n");

        /* "allvector" outputs the entire vector */

        if ((dat_datctl.control2 & CTL2_ALLVECTOR) != 0)
          show_ovector(ovector, oveccount);
        }
      break;

      case PCRE2_ERROR_BADUTFOFFSET:
      fprintf(outfile, "Error %d (bad UTF-%d offset)\n", capcount, test_mode);
      break;

      default:
      fprintf(outfile, "Failed: error %d: ", capcount);
      if (!print_error_message(capcount, "", "")) return PR_ABEND;
      if (capcount <= PCRE2_ERROR_UTF8_ERR1 &&
          capcount >= PCRE2_ERROR_UTF32_ERR2)
        {
        PCRE2_SIZE startchar;
        PCRE2_GET_STARTCHAR(startchar, match_data);
        fprintf(outfile, " at offset %" SIZ_FORM, startchar);
        }
      fprintf(outfile, "\n");
      break;
      }

    break;  /* Out of the /g loop */
    }       /* End of failed match handling */

  /* Control reaches here after a match. If we are not doing a global search,
  we are done. Otherwise, we adjust the parameters for the next match and
  continue the matching loop. */

  NEXT_MATCH:

  if ((dat_datctl.control & CTL_ANYGLOB) == 0)
    break;
  else
    {
    PCRE2_SIZE new_start_offset = (PCRE2_SIZE)-1;
    BOOL rc_nextmatch;

    /* Use pcre2_next_match() to safely advance. This guarantees that the start
    offset will advance, except after an empty match, in which case it sets
    the PCRE2_NOTEMPTY_ATSTART flag to ensure the next match does not return a
    duplicate. */

    PCRE2_NEXT_MATCH(rc_nextmatch, match_data, &new_start_offset, &g_notempty);
    if (!rc_nextmatch) break;  /* Out of the /g loop */

    /* For a normal global (/g) iteration, update the start offset, leaving
    other parameters alone. */

    if ((dat_datctl.control & CTL_GLOBAL) != 0)
      {
      dat_datctl.offset = new_start_offset;
      }

    /* For altglobal, just update the pointer and length. */

    else
      {
      pp += new_start_offset * code_unit_size;
      len -= new_start_offset * code_unit_size;
      ulen -= new_start_offset;
      if (arg_ulen != PCRE2_ZERO_TERMINATED) arg_ulen -= new_start_offset;
      }
    }
  }  /* End of global loop */

/* All matching is done; show the resulting heapframe size if requested. */

if ((dat_datctl.control2 & CTL2_HEAPFRAMES_SIZE) != 0 &&
    (dat_datctl.control & CTL_DFA) == 0)
  show_heapframes_size();

show_memory = FALSE;
return PR_OK;
}



/*************************************************
*      Initialise the mode-dependent globals     *
*************************************************/

/* Sets up the global variables used for the current test mode. */

static void
init_globals(void)
{
  
#define CREATECONTEXTS \
  G(general_context,BITS) = G(pcre2_general_context_create_,BITS)(&my_malloc, &my_free, NULL); \
  G(general_context_copy,BITS) = G(pcre2_general_context_copy_,BITS)(G(general_context,BITS)); \
  G(default_pat_context,BITS) = G(pcre2_compile_context_create_,BITS)(G(general_context,BITS)); \
  G(pat_context,BITS) = G(pcre2_compile_context_copy_,BITS)(G(default_pat_context,BITS)); \
  G(default_dat_context,BITS) = G(pcre2_match_context_create_,BITS)(G(general_context,BITS)); \
  G(dat_context,BITS) = G(pcre2_match_context_copy_,BITS)(G(default_dat_context,BITS)); \
  G(default_con_context,BITS) = G(pcre2_convert_context_create_,BITS)(G(general_context,BITS)); \
  G(con_context,BITS) = G(pcre2_convert_context_copy_,BITS)(G(default_con_context,BITS)); \
  G(match_data,BITS) = G(pcre2_match_data_create_,BITS)(max_oveccount, G(general_context,BITS))

/* Set a default parentheses nest limit that is large enough to run the
standard tests (this also exercises the function). */

pcre2_set_parens_nest_limit(default_pat_context, PARENS_NEST_DEFAULT);
}



/* End of pcre2test_inc.h */
