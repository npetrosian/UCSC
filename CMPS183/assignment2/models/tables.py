# Define your tables below (or better in another model file) for example
#
# >>> db.define_table('mytable', Field('myfield', 'string'))
#
# Fields can be 'string','text','password','integer','double','boolean'
#       'date','time','datetime','blob','upload', 'reference TABLENAME'
# There is an implicit 'id integer autoincrement' field
# Consult manual for more options, validators, etc.




# after defining tables, uncomment below to enable auditing
# auth.enable_record_versioning(db)

def get_user_email():
    return None if auth.user is None else auth.user.email

db.define_table('product',
                Field('product_name', 'text'),
                Field('product_description', 'text'), # At most 512 characters
                Field('product_quantity', 'integer', default=0), # "unlimited"
                Field('product_quantity_sold', 'integer', default=0),
                Field('product_price', 'double', default = 0.00),
                Field('product_cost', 'double', default = 0.00),
                Field('product_starred', 'boolean', default=False),
                Field('product_creator', default=get_user_email())
                )

db.product.id.readable = False
db.product.product_starred.readable = False
db.product.product_starred.writable = False
db.product.product_creator.readable = False
db.product.product_creator.writable = False
db.product.product_quantity_sold.readable = False
db.product.product_quantity_sold.writable = False

db.product.product_quantity.requires = IS_INT_IN_RANGE(0, 1e10)
db.product.product_cost.requires = IS_FLOAT_IN_RANGE(0.00, 1e10)
db.product.product_price.requires = IS_FLOAT_IN_RANGE(0.00, 1e10)
