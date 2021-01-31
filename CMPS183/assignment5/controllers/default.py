# -*- coding: utf-8 -*-
# -------------------------------------------------------------------------
# This is a sample controller
# this file is released under public domain and you can use without limitations
# -------------------------------------------------------------------------

import json
import os
import traceback

# ---- example index page ----
def index():
    return dict()

def get_products():
    """Gets the list of products, possibly in response to a query."""
    t = request.vars.q.strip()
    if request.vars.q:
        q = ((db.product.product_name.contains(t)) |
             (db.product.description.contains(t)))
    else:
        q = db.product.id > 0
    products = db(q).select(db.product.ALL)
    # Fixes some fields, to make it easy on the client side.
    for p in products:
        # p.image_url = URL('default', 'download', args=[p.image])
        p.desired_quantity = min(1, p.quantity)
        p.cart_quantity = 0
    return response.json(dict(
        products=products,
    ))

priv_folder = os.path.join(request.folder, 'private')
key_file = os.path.join(priv_folder, 'stripe_keys.json')
# STRIPE_KEY_INFO = json.load(open(key_file))

def purchase():
    """Ajax function called when a customer orders and pays for the cart."""
    if not URL.verify(request, hmac_key=session.hmac_key):
        raise HTTP(500)
    # Creates the charge.
    import stripe
    stripe.set_app_info('Luca de Alfaro teaching site', version="2.0", url="http://www.soe.ucsc.edu/~luca")
    # Your secret key.
    stripe.api_key = STRIPE_KEY_INFO['private_key']
    token = json.loads(request.vars.transaction_token)
    amount = float(request.vars.amount)
    try:
        charge = stripe.Charge.create(
            amount=int(amount * 100),
            currency="usd",
            source=token['id'],
            description="Purchase",
        )
        logger.info("The charge was successful")
    except stripe.error.CardError as e:
        logger.info("The card has been declined.")
        logger.info("%r" % traceback.format_exc())
        return response.json(dict(result="nok"))
    db.customer_order.insert(
        customer_info=request.vars.customer_info,
        transaction_token=json.dumps(token),
        cart=request.vars.cart)
    return response.json(dict(result="ok"))


# Normally here we would check that the user is an admin, and do programmatic
# APIs to add and remove products to the inventory, etc.
@auth.requires_login()
def product_management():
    q = db.product # This queries for all products.
    form = SQLFORM.grid(
        q,
        editable=True,
        create=True,
        user_signature=True,
        deletable=True,
        fields=[db.product.product_name, db.product.quantity, db.product.price,
                db.product.image],
        details=True,
    )
    return dict(form=form)

@auth.requires_login()
def view_orders():
    q = db.customer_order # This queries for all products.
    db.customer_order.customer_info.represent = lambda v, r: nicefy(v)
    db.customer_order.transaction_token.represent = lambda v, r: nicefy(v)
    db.customer_order.cart.represent = lambda v, r: nicefy(v)
    form = SQLFORM.grid(
        q,
        editable=True,
        create=True,
        user_signature=True,
        deletable=True,
        details=True,
    )
    return dict(form=form)

def products():
    db.product.id.readable = db.product.id.writable = False
    grid = SQLFORM.grid(
        db.product,
        csv=False
    )
    return dict(grid=grid)

# ---- API (example) -----
@auth.requires_login()
def api_get_user_email():
    if not request.env.request_method == 'GET': raise HTTP(403)
    return response.json({'status':'success', 'email':auth.user.email})

# ---- Smart Grid (example) -----
@auth.requires_membership('admin') # can only be accessed by members of admin groupd
def grid():
    response.view = 'generic.html' # use a generic view
    tablename = request.args(0)
    if not tablename in db.tables: raise HTTP(403)
    grid = SQLFORM.smartgrid(db[tablename], args=[tablename], deletable=False, editable=False)
    return dict(grid=grid)

# ---- Embedded wiki (example) ----
def wiki():
    auth.wikimenu() # add the wiki to the menu
    return auth.wiki() 

# ---- Action for login/register/etc (required for auth) -----
def user():
    """
    exposes:
    http://..../[app]/default/user/login
    http://..../[app]/default/user/logout
    http://..../[app]/default/user/register
    http://..../[app]/default/user/profile
    http://..../[app]/default/user/retrieve_password
    http://..../[app]/default/user/change_password
    http://..../[app]/default/user/bulk_register
    use @auth.requires_login()
        @auth.requires_membership('group name')
        @auth.requires_permission('read','table name',record_id)
    to decorate functions that need access control
    also notice there is http://..../[app]/appadmin/manage/auth to allow administrator to manage users
    """
    return dict(form=auth())

# ---- action to server uploaded static content (required) ---
@cache.action()
def download():
    """
    allows downloading of uploaded files
    http://..../[app]/default/download/[filename]
    """
    return response.download(request, db)

def call():
    """
    exposes services. for example:
    http://..../[app]/default/call/jsonrpc
    decorate with @services.jsonrpc the functions to expose
    supports xml, json, xmlrpc, jsonrpc, amfrpc, rss, csv
    """
    return service()
