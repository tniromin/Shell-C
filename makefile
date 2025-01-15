ARG ?= DefaultValue
git:
	git add .
	git commit -m "$(ARG)"
	git push origin master


	
	# echo $(ARG)
all:
	g++ main.cpp -o main
	./main
	
new:
	g++ main.cpp -o main

run: 
	./main
