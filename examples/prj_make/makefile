.PHONY: test
test:
	make -C umtktcp test
	make -C emarket this
	make -C houselight this
	make -C houselight doc
	make -C tree_server this
	make -C tree_server doc
	make -C acs this
	make -C acs doc
	make -C alarms_db this
	make -C alarms_db doc
	make -C product_loader this
	make -C product_loader doc
	make -C orders_loader this
	make -C orders_loader doc
	make -C account_manager this
	make -C account_manager doc
	make -C trading_db this
	make -C trading_db doc


.PHONY: this
this:
	make -C emarket this
	make -C houselight this
	make -C tree_server this
	make -C acs this
	make -C alarms_db this
	make -C product_loader this
	make -C orders_loader this
	make -C account_manager this
	make -C trading_db this

.PHONY: clean
clean:
	make -C emarket clean
	make -C houselight clean
	make -C tree_server clean
	make -C acs clean
	make -C alarms_db clean
	make -C product_loader clean
	make -C orders_loader clean
	make -C account_manager clean
	make -C trading_db clean
	find . -name 'ct__*' | xargs rm