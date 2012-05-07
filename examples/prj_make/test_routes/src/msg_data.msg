BEGIN_INIT

NAMESPACES = ['tr']
INCLUDES = [ ]

END_INIT



//{dest: IP_EU, origin: IP_GS1, qe_name: ALL_GS, subject: 'ALL._GS1.testing'}
sub_route  [< >]
{
    origin      (or)    :   string
    dest        (dest)  :   string
    qe_name     (qen)   :   string
    subject     (sub)   :   string
}

sub_ip_names  [< KEY:name >]
{
    name      (n)    :   string
    ip        (i)  :   string
}

