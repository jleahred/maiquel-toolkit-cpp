.PHONY: test
test:
	make -C umtktcp test
	make -C emarket this
	make -C houselight this
	make -C tree_server_cfg this
	make -C acs this
	make -C alarms_db this
	make -C product_loader this
	make -C orders_loader this
	make -C account_manager this
	make -C trading_db this
	make -C quantity_filter this
	make -C prodinfo_grant this


.PHONY: this
this:
	make -C emarket this
	make -C houselight this
	make -C tree_server_cfg this
	make -C acs this
	make -C alarms_db this
	make -C product_loader this
	make -C orders_loader this
	make -C account_manager this
	make -C trading_db this
	make -C quantity_filter this
	make -C prodinfo_grant this

.PHONY: clean
clean:
	make -C emarket clean
	make -C houselight clean
	make -C tree_server_cfg clean
	make -C acs clean
	make -C alarms_db clean
	make -C product_loader clean
	make -C orders_loader clean
	make -C account_manager clean
	make -C trading_db clean
	make -C quantity_filter clean
	make -C prodinfo_grant clean
	find . -name 'ct__*' | xargs rm


.PHONY: doc
doc:
	make -C emarket doc
	make -C houselight doc
	make -C tree_server_cfg doc
	make -C acs doc
	make -C alarms_db doc
	make -C product_loader doc
	make -C orders_loader doc
	make -C account_manager doc
	make -C trading_db doc
	make -C quantity_filter doc
	make -C prodinfo_grant doc
