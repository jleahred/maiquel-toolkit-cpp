// Tags

[jle_temp_and_run]
++++++++++++++++++++++++
run=[('bash analysis_fields.bash', 'field_analysis.txt', 'wt')]
print ''

file_name='analysis_fields.bash'


cd {docdir}/../../../src/components


find {docdir}/../../../src/components  -name '*.msg' | xargs python {docdir}/../../../src/components/tools/msg_analysis.py


++++++++++++++++

include::/tmp/adoc/field_analysis.txt[]



//    trick

[jle_temp_and_run]
++++++++++++++++++++++++
run=[('bash analysis_fields.bash', 'field_analysist.txt', 'wt')]
print ''

file_name='analysis_fields.bash'


cd {docdir}/../../src/components


find {docdir}/../../src/components  -name '*.msg' | xargs python {docdir}/../../src/components/tools/msg_analysis.py


++++++++++++++++

include::/tmp/adoc/field_analysist.txt[]
