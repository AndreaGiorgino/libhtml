#!/usr/bin/env bash

usage='''NAME
    build - libhtml build script

SYNOPSIS
    build [options...] [target]

DESCRIPTION
    libhtml script for target builds. If no target has been provided,
    then ''build'' is used.

OPTIONS
    -v, --version
        Print the script version message and exit.

    -h, --help
        Print the script help message and exit.

    --autorun
        Autorun after build based on the target.

TARGETS
    build
        Build libhtml.

    debug
        Build libhtml in debug mode.

    test
        Build libhtml and tests. If ''--autorun'' has been provided, run
        the tests.

    example
        Build libhtml and example. If ''--autorun'' has been provided, run
        the example.
'''

version='1.0.0'

while true; do
    case $1 in
        -h | --help)
            echo "${usage}"
            exit 0
            ;;
        -v | --version)
            echo "build v${version}"
            exit 0
            ;;
        --autorun)
            autorun=true
            shift;
            ;;
        --)
            shift;
            break;
            ;;
        -*)
            echo "Invalid option '${1}'"
            echo ''
            echo "${usage}"
            exit 2
            ;;
        *)
            break;
            ;;
    esac
done

case $1 in
    '' | build)
        cmake -B build && \
            cmake --build build --parallel $(($(nproc) - 1))
        ;;
    debug)
        cmake -B build -DDEBUG=ON && \
            cmake --build build --parallel $(($(nproc) - 1))
        ;;
    test)
        cmake -B build -DLIBHTML_BUILD_TESTING=ON && \
            cmake --build build --parallel $(($(nproc) - 1))

        [[ $? == 0 && $autorun ]] && \
            ctest --test-dir build --output-on-failure
        ;;
    example)
        cmake -B build -DLIBHTML_BUILD_EXAMPLE=ON && \
            cmake --build build --parallel $(($(nproc) - 1))

        [[ $? == 0 && $autorun ]] && \
            ./build/example/example
        ;;
    *)
        echo "Invalid target '${1}'"
        echo ''
        echo "${usage}"
        exit 2
        ;;
esac

exit $?
