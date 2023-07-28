.PHONY: clean All

All:
	@echo "----------Building project:[ orxConfigTemplateToWiki - Debug ]----------"
	@cd "orxConfigTemplateToWikiConverter" && "$(MAKE)" -f  "orxConfigTemplateToWiki.mk"
clean:
	@echo "----------Cleaning project:[ orxConfigTemplateToWiki - Debug ]----------"
	@cd "orxConfigTemplateToWikiConverter" && "$(MAKE)" -f  "orxConfigTemplateToWiki.mk" clean
