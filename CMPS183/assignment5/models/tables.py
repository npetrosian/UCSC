import datetime

def get_user_email():
    return None if auth.user is None else auth.user.email

def get_name():
    return None if auth.user is None else auth.user.first_name + ' ' + auth.user.last_name

db.define_table('product',
    Field('name', default=''),
    Field('description', default=''),
    Field('price', 'float', default=0.00),
    Field('quantity', 'integer')
)
db.product.id.readable = db.product.id.writable = False

db.define_table('review',
    Field('product_id', 'reference product'),
    Field('rating', 'integer', default=0),
    Field('body', 'text', default=''),
    Field('email', default=get_user_email()),
    Field('name', default=get_name())
)

db.define_table('customer_order',
    Field('order_date', default=datetime.datetime.utcnow()),
    Field('customer_info', 'blob'),
    Field('transaction_token', 'blob'),
    Field('cart', 'blob'),
)

db.define_table('shopping_cart',
    Field('user_email'),
    Field('product_id', 'reference product'),
    Field('amount', 'integer'),
)

# Let's define a secret key for stripe transactions.
from gluon.utils import web2py_uuid
if session.hmac_key is None:
    session.hmac_key = web2py_uuid()

# after defining tables, uncomment below to enable auditing
# auth.enable_record_versioning(db)

import json

def nicefy(b):
    if b is None:
        return 'None'
    obj = json.loads(b)
    s = json.dumps(obj, indent=2)
    return s
