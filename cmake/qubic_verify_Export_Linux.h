
#ifndef QUBIC_VERIFY_EXPORT_H
#define QUBIC_VERIFY_EXPORT_H

#ifdef QUBIC_VERIFY_STATIC_DEFINE
#  define QUBIC_VERIFY_EXPORT
#  define QUBIC_VERIFY_NO_EXPORT
#else
#  ifndef QUBIC_VERIFY_EXPORT
#    ifdef qubic_verify_EXPORTS
        /* We are building this library */
#      define QUBIC_VERIFY_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define QUBIC_VERIFY_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef QUBIC_VERIFY_NO_EXPORT
#    define QUBIC_VERIFY_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef QUBIC_VERIFY_DEPRECATED
#  define QUBIC_VERIFY_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef QUBIC_VERIFY_DEPRECATED_EXPORT
#  define QUBIC_VERIFY_DEPRECATED_EXPORT QUBIC_VERIFY_EXPORT QUBIC_VERIFY_DEPRECATED
#endif

#ifndef QUBIC_VERIFY_DEPRECATED_NO_EXPORT
#  define QUBIC_VERIFY_DEPRECATED_NO_EXPORT QUBIC_VERIFY_NO_EXPORT QUBIC_VERIFY_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef QUBIC_VERIFY_NO_DEPRECATED
#    define QUBIC_VERIFY_NO_DEPRECATED
#  endif
#endif

#endif /* QUBIC_VERIFY_EXPORT_H */
