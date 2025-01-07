ARG ?= DefaultValue
git:
	git add .
	git commit -m "$(ARG)"
	git push origin master


	
	# echo $(ARG)