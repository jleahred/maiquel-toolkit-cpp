.PHONY: test
test:
	make -C umtktcp test
	make -C emarket release
	make -C houselight release
	make -C tree_server_cfg release
	make -C acs release
	make -C alarms_db release
	make -C product_loader release
	make -C orders_loader release
	make -C execs_loader release
	make -C account_manager release
	make -C trading_db release
	make -C quantity_filter release
	make -C prodinfo_grant release
	make -C republic_prices release
	make -C hist_execs release
	make -C test_routes release


.PHONY: release
release:
	make -C emarket release
	make -C houselight release
	make -C tree_server_cfg release
	make -C acs release
	make -C alarms_db release
	make -C product_loader release
	make -C orders_loader release
	make -C execs_loader release
	make -C account_manager release
	make -C trading_db release
	make -C quantity_filter release
	make -C prodinfo_grant release
	make -C republic_prices release
	make -C hist_execs release
	make -C test_routes release

.PHONY: clean
clean:
	make -C emarket clean
	make -C houselight clean
	make -C tree_server_cfg clean
	make -C acs clean
	make -C alarms_db clean
	make -C product_loader clean
	make -C orders_loader clean
	make -C execs_loader clean
	make -C account_manager clean
	make -C trading_db clean
	make -C quantity_filter clean
	make -C prodinfo_grant clean
	make -C republic_prices clean
	make -C hist_execs clean
	make -C test_routes clean
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
	make -C execs_loader doc
	make -C account_manager doc
	make -C trading_db doc
	make -C quantity_filter doc
	make -C prodinfo_grant doc
	make -C republic_prices doc
	make -C hist_execs doc
	make -C test_routes doc
