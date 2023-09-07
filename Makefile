all: compile_all_assignments

assure_utils:
	@for assignment in assignment-*/ ; do \
		echo "Copying utils: $$assignment"; \
		cd $$assignment; \
		rm -rf utils; \
		rm -f config.h; \
		cp -r ../utils .; \
		cp ../config.h .; \
		cd ..; \
	done

compile_all_assignments: assure_utils
	@for assignment in assignment-*/ ; do \
		echo "Compiling: $$assignment"; \
		cd $$assignment; \
		gcc *.c utils/**.c -o $$assignment; \
		cd ..; \
	done

package_all_assignments: compile_all_assignments
	@for assignment in assignment-*/ ; do \
		echo "Packaging: $$assignment"; \
		cd $$assignment; \
		tar -czf ../$$assignment.tar.gz * ../disclaimer.txt; \
		cd ..; \
	done

clean:
	@for assignment in assignment-*/ ; do \
		echo "Cleaning: $$assignment"; \
		cd $$assignment; \
		rm -f *.o; \
		rm -f *.tar.gz; \
		rm -f $$(basename $$assignment); \
		rm -rf utils; \
		rm -f config.h; \
		cd ..; \
	done

ASSIGNMENT?=1

compile_assignment: assure_utils
	@echo "Compiling: assignment-$(ASSIGNMENT)"
	@cd assignment-$(ASSIGNMENT); \
	gcc *.c utils/**.c -o assignment-$(ASSIGNMENT)

package_assignment: compile_assignment
	@echo "Packaging: assignment-$(ASSIGNMENT)"
	@cd assignment-$(ASSIGNMENT); \
	tar -czf ../assignment-$(ASSIGNMENT).tar.gz * ../disclaimer.txt

run_assignment: clean compile_assignment
	@echo "Running assignment-$(ASSIGNMENT)"
	@echo "=============================="
	@cd assignment-$(ASSIGNMENT); \
	./assignment-$(ASSIGNMENT)
