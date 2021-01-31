# Define your tables below (or better in another model file) for example
#
# >>> db.define_table('mytable', Field('myfield', 'string'))
#
# Fields can be 'string','text','password','integer','double','boolean'
#       'date','time','datetime','blob','upload', 'reference TABLENAME'
# There is an implicit 'id integer autoincrement' field
# Consult manual for more options, validators, etc.


db.define_table('product',
    Field('product_name'),
    Field('product_quantity', 'integer'),
    Field('sales_price', 'float'),
)

def get_product_name(p):
    return None if p is None else p.product_name

def get_profile_email(p):
    return None if p is None else p.profile_email

db.define_table('profile',
    # Field('profile_email', 'text'),
    Field('profile_email'),
    Field('profile_name', 'text'),
    Field('profile_street', 'text'),
    Field('profile_city', 'text'),
    Field('profile_zip', 'text'),
)

db.define_table('orders',
    Field('orders_email', 'reference profile'),
    Field('orders_product_id', 'reference product'),
    Field('orders_quantity', 'integer'),
    Field('orders_date', 'datetime', default=request.now),
    Field('orders_amount_paid', 'float'),
)

db.orders.orders_email.readable = True
db.orders.orders_email.writable = False

db.orders.orders_product_id.readable = True
db.orders.orders_product_id.writable = False

db.orders.orders_date.readable = True
db.orders.orders_date.writable = False

db.orders.orders_amount_paid.readable = True
db.orders.orders_amount_paid.writable = False
db.orders.id.readable = False

db.product.id.readable = False


db.profile.id.readable = False


# after defining tables, uncomment below to enable auditing
auth.enable_record_versioning(db)
