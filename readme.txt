sql£º
SELECT customer_credit_flow_id,balance,customer_master_id FROM apollo_os.t_customer_credit_flow where expire_date='2016-03-18' and balance>0 and dr=0 and transaction_type=0


update apollo_os.t_customer_credit_flow set balance=0 where customer_credit_flow_id='JAVVUWVBFV5QJIPNY79T'

update apollo_os.t_customer_master set credit_balance=0 where customer_master_id='JAVVUWUGS2OBYQ381HNP'



