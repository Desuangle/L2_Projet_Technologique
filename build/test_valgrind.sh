ctest -T memcheck;
cat ./Testing/Temporary/MemoryChecker.*.log > memoryleaks.txt;
echo "Memory leaks rajoutes dans memoryleaks.txt";
