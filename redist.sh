rm -rf redist_release redist_debug

mkdir -p redist_release/lib redist_release/include redist_release/bin
mkdir -p redist_debug/lib redist_debug/include redist_debug/bin

find out/Release -name *.a -exec cp {} redist_release/lib/ \;
find out/Release -perm +111 -type f -exec cp {} redist_release/bin/ \;

find out/Debug -name *.a -exec cp {} redist_debug/lib/ \;
find out/Debug -perm +111 -type f -exec cp {} redist_debug/bin/ \;
