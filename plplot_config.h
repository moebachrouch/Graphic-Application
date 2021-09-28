// Configured (by CMake) macros for PLplot that are required for the
// core build but _not_ required for the build of the installed
// examples (and presumably any user applications).  Therefore, the
// configured plplot_config.h should not be installed.  In contrast,
// include/plConfig.h.in (note, the configured plConfig.h result
// #includes plplot_config.h for the core build because PLPLOT_HAVE_CONFIG_H
// is #defined in that case) contains configured macros that are
// required for the core build, installed examples build, and build of
// user applications.  Therefore, in contrast to plplot_config.h,
// plConfig.h should be installed.
//
// Maintenance issue: in makes no sense to configure duplicate macros
// for both plplot_config.h and plConfig.h.  Therefore, when adding a macro
// decide which file to put it in depending on whether the result is
// needed for the installed examples build or not.  Furthermore, move
// configured macros from one file to the other as needed depending on
// that criterion, but do not copy them.
//

// Location of executables
#define BIN_DIR                  "C:/Libs/plplot-5.11.1/buildmingw/install/bin"

// Location of Build tree
#define BUILD_DIR                "C:/Libs/plplot-5.11.1/buildmingw"

// Location of package data files
#define DATA_DIR                 "C:/Libs/plplot-5.11.1/buildmingw/install/share/plplot5.11.1"

// Location of dynamically loaded drivers
#define DRV_DIR                  "C:/Libs/plplot-5.11.1/buildmingw/install/lib/plplot5.11.1/drivers"

// Name of the default cmap0 palette to use
#define PL_DEFAULT_CMAP0_FILE    "cmap0_default.pal"

// Name of the default cmap1 palette to use
#define PL_DEFAULT_CMAP1_FILE    "cmap1_default.pal"

// Define if support for deprecated plplot functions should be compiled
/* #undef PL_DEPRECATED */

// Define if there is support for dynamically loaded drivers
#define ENABLE_DYNDRIVERS

// Define to 1 if you have the <cmath> header file.
#define HAVE_CMATH 1

// Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
//
#define HAVE_DIRENT_H 1

// Define to 1 if you have the <dlfcn.h> header file.
/* #undef HAVE_DLFCN_H */

// Define if [freetype] is available
/* #undef PL_HAVE_FREETYPE */

// Define if [shapelib] is available
/* #undef HAVE_SHAPELIB */

// Define if [agg] is available
/* #undef HAVE_AGG */

// Define to 1 if you have the <glib.h> header file.
/* #undef HAVE_GLIB_H */

// Define to 1 if you have the <glib-object.h> header file.
/* #undef HAVE_GLIB_OBJECT_H */

// Define to 1 if you have the <gtk/gtk.h> header file.
/* #undef HAVE_GTK_GTK_H */

// Define to 1 if you have the <inttypes.h> header file.
/* #undef HAVE_INTTYPES_H */

// Define if [incr], [Tcl] is available
/* #undef HAVE_ITCL */

// Define to 1 if you have the <itclDecls.h> header file.
/* #undef HAVE_ITCLDECLS_H */

// Define if Tk is enabled and X11 has been found.
/* #undef ENABLE_tkX */

// Define if [incr], [Tk] is available
/* #undef HAVE_ITK */

// Define to 1 if you have the <jni.h> header file.
/* #undef HAVE_JNI_H */

// Define to 1 if you have the <libart_lgpl/libart.h> header file.
/* #undef HAVE_LIBART_LGPL_LIBART_H */

// Define if libunicode is available
/* #undef HAVE_LIBUNICODE */

// Define to 1 if you have the <math.h> header file.
/* #undef HAVE_MATH_H */

// Define to 1 if you have the <memory.h> header file.
/* #undef HAVE_MEMORY_H */

// Define to 1 if the function mkstemp is available.
/* #undef PL_HAVE_MKSTEMP */

// Define to 1 if the function mkdtemp is available.
/* #undef PL_HAVE_MKDTEMP */

// Define to 1 if the function mkfifo is available.
/* #undef PL_HAVE_MKFIFO */

// Define to 1 if you have the <ndir.h> header file, and it defines `DIR'.
/* #undef HAVE_NDIR_H */

// Define if libpango is available
/* #undef HAVE_PANGO */

// Define if popen is available
#define HAVE_POPEN

// Define if _NSGetArgc is available
/* #undef HAVE_NSGETARGC */

// Define if pthreads is available
/* #undef PL_HAVE_PTHREAD */

// Define if Qhull is available
/* #undef PL_HAVE_QHULL */

// Define to 1 if you have the <stdlib.h> header file.
/* #undef HAVE_STDLIB_H */

// Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
//
/* #undef HAVE_SYS_DIR_H */

// Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
//
/* #undef HAVE_SYS_NDIR_H */

// Define to 1 if you have the <sys/stat.h> header file.
/* #undef HAVE_SYS_STAT_H */

// Define to 1 if you have the <sys/types.h> header file.
/* #undef HAVE_SYS_TYPES_H */

// Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible.
/* #undef HAVE_SYS_WAIT_H */

// Define to 1 if you have the <termios.h> header file.
/* #undef HAVE_TERMIOS_H */

// Define to 1 if you have the <crt_externs.h> header file.
/* #undef HAVE_CRT_EXTERNS_H */

// Define to 1 if the function unlink is available
#define PL_HAVE_UNLINK 1

// Define to 1 if you have the `vfork' function.
/* #undef HAVE_VFORK */

// Define to 1 if you have the <vfork.h> header file.
/* #undef HAVE_VFORK_H */

// Include sys/type.h if needed
#define NEED_SYS_TYPE_H

// Name of package
#define PACKAGE    "plplot"

// Define if the win32 ltdl implementation should be used
#define LTDL_WIN32

// Portable definition for PTHREAD_MUTEX_RECURSIVE
#define PLPLOT_MUTEX_RECURSIVE             

// Directory containing fonts that are accessible from freetype
#define PL_FREETYPE_FONT_DIR               ""

// MONO font accessible from freetype
#define PL_FREETYPE_MONO                   ""

// MONO_BOLD font accessible from freetype
#define PL_FREETYPE_MONO_BOLD              ""

// MONO_BOLD_ITALIC font accessible from freetype
#define PL_FREETYPE_MONO_BOLD_ITALIC       ""

// MONO_BOLD_OBLIQUE font accessible from freetype
#define PL_FREETYPE_MONO_BOLD_OBLIQUE      ""

// MONO_ITALIC font accessible from freetype
#define PL_FREETYPE_MONO_ITALIC            ""

// MONO_OBLIQUE font accessible from freetype
#define PL_FREETYPE_MONO_OBLIQUE           ""

// SANS font accessible from freetype
#define PL_FREETYPE_SANS                   ""

// SANS_BOLD font accessible from freetype
#define PL_FREETYPE_SANS_BOLD              ""

// SANS_BOLD_ITALIC font accessible from freetype
#define PL_FREETYPE_SANS_BOLD_ITALIC       ""

// SANS_BOLD_OBLIQUE font accessible from freetype
#define PL_FREETYPE_SANS_BOLD_OBLIQUE      ""

// SANS_ITALIC font accessible from freetype
#define PL_FREETYPE_SANS_ITALIC            ""

// SANS_OBLIQUE font accessible from freetype
#define PL_FREETYPE_SANS_OBLIQUE           ""

// SCRIPT font accessible from freetype
#define PL_FREETYPE_SCRIPT                 ""

// SCRIPT_BOLD font accessible from freetype
#define PL_FREETYPE_SCRIPT_BOLD            ""

// SCRIPT_BOLD_ITALIC font accessible from freetype
#define PL_FREETYPE_SCRIPT_BOLD_ITALIC     ""

// SCRIPT_BOLD_OBLIQUE font accessible from freetype
#define PL_FREETYPE_SCRIPT_BOLD_OBLIQUE    ""

// SCRIPT_ITALIC font accessible from freetype
#define PL_FREETYPE_SCRIPT_ITALIC          ""

// SCRIPT_OBLIQUE font accessible from freetype
#define PL_FREETYPE_SCRIPT_OBLIQUE         ""

// SERIF font accessible from freetype
#define PL_FREETYPE_SERIF                  ""

// SERIF_BOLD font accessible from freetype
#define PL_FREETYPE_SERIF_BOLD             ""

// SERIF_BOLD_ITALIC font accessible from freetype
#define PL_FREETYPE_SERIF_BOLD_ITALIC      ""

// SERIF_BOLD_OBLIQUE font accessible from freetype
#define PL_FREETYPE_SERIF_BOLD_OBLIQUE     ""

// SERIF_ITALIC font accessible from freetype
#define PL_FREETYPE_SERIF_ITALIC           ""

// SERIF_OBLIQUE font accessible from freetype
#define PL_FREETYPE_SERIF_OBLIQUE          ""

// Symbol font accessible from freetype
#define PL_FREETYPE_SYMBOL                 ""

// SYMBOL_BOLD font accessible from freetype
#define PL_FREETYPE_SYMBOL_BOLD            ""

// SYMBOL_BOLD_ITALIC font accessible from freetype
#define PL_FREETYPE_SYMBOL_BOLD_ITALIC     ""

// SYMBOL_BOLD_OBLIQUE font accessible from freetype
#define PL_FREETYPE_SYMBOL_BOLD_OBLIQUE    ""

// SYMBOL_ITALIC font accessible from freetype
#define PL_FREETYPE_SYMBOL_ITALIC          ""

// SYMBOL_OBLIQUE font accessible from freetype
#define PL_FREETYPE_SYMBOL_OBLIQUE         ""

// Define as the return type of signal handlers (`int' or `void').
#define RETSIGTYPE                         void

// Location of Source tree
#define SOURCE_DIR                         "C:/Libs/plplot-5.11.1"

// Define to 1 if you have the ANSI C header files.
#define STDC_HEADERS 1

// Location of Tcl stuff
#define TCL_DIR                    "C:/Libs/plplot-5.11.1/buildmingw/install/share/plplot5.11.1/tcl"
// Consistent package versions for Itcl and friends found by PLplot
// If PLplot could not find consistent values these are set to 0.0.0
#define PLPLOT_ITCL_VERSION        "0.0.0"
#define PLPLOT_ITK_VERSION         "0.0.0"
#define PLPLOT_IWIDGETS_VERSION    "0.0.0"

// Define if csa is desired
#define WITH_CSA

// Define if want to use general fill_intersection_polygon approach
// rather than the traditional code to fill the intersection of a polygon with
// the clipping limits.
/* #undef USE_FILL_INTERSECTION_POLYGON */

// Define to `char *' if <sys/types.h> does not define.
/* #undef caddr_t */

// Define to `int' if <sys/types.h> does not define.
/* #undef pid_t */

// Define as `fork' if `vfork' does not work.
/* #undef vfork */

// Define if the PLplot build uses Qt5 (rather than Qt4).
/* #undef PLPLOT_USE_QT5 */
