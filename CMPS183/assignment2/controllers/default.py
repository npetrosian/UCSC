# -*- coding: utf-8 -*-
# this file is released under public domain and you can use without limitations

# -------------------------------------------------------------------------
# This is a sample controller
# - index is the default action of any application
# - user is required for authentication and authorization
# - download is for downloading files uploaded in the db (does streaming)
# -------------------------------------------------------------------------


def index():
    """
    example action using the internationalization operator T and flash
    rendered by views/default/index.html or views/generic.html

    if you need a simple wiki simply replace the two lines below with:
    return auth.wiki()
    """
    response.flash = T("CMPS 183 Homework 2")
    rows = db(db.product).select()
    return dict(message=T('Welcome to web2py!'), rows=rows)


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

@auth.requires_login()
def createProduct():
    """More sophisticated way, in which we use web2py to come up with the form."""
    form = SQLFORM(db.product)
    # We can process the form.  This will check that the request is a POST,
    # and also perform validation, but in this case there is no validation.
    # THIS process() also inserts.
    if form.process().accepted:
        redirect(URL('default', 'list_page'))
    # We ask web2py to lay out the form for us.
    logger.info("My session is: %r" % session)
    return dict(form=form)

def list_page():
    """Displays the list of rows"""
    rows = db(db.product).select()
    return dict(
        rows=rows,
    )

def test_page():
    """Displays the list of rows"""
    rows = db(db.product).select()
    return dict(
        rows=rows,
    )

@auth.requires_signature()
def star_clicked():
    logger.info("Star was clicked parameter = %r", request.args(0))
    record = db(db.product.id == request.args(0)).select().first()
    if record: 
        flag = record.product_starred
        flag = not flag
        db(db.product.id == request.args(0)).update(product_starred = flag)

    redirect(URL('default', 'list_page'))

@auth.requires_signature()
def increment_clicked():
    logger.info("The + button was clicked parameter = %r", request.args(0))
    record = db(db.product.id == request.args(0)).select().first()

    if record:
        count = record.product_quantity
        count = count + 1
        db(db.product.id == request.args(0)).update(product_quantity = count)

    redirect(URL('default', 'list_page'))

@auth.requires_signature()
def decrement_clicked():
    logger.info("The - button was clicked")
    record = db(db.product.id == request.args(0)).select().first()

    if record:
        count = record.product_quantity
        count = count - 1
        if count >= 0:
             db(db.product.id == request.args(0)).update(product_quantity = count)
             count = record.product_quantity_sold
             count = count + 1
             db(db.product.id == request.args(0)).update(product_quantity_sold = count)

    redirect(URL('default', 'list_page'))

@auth.requires_signature()
def edit():
    logger.info("The edit button was clicked")
    record = db(db.product.id == request.args(0)).select().first()
    form = SQLFORM(db.product, record)

    if form.process().accepted:
        redirect(URL('default', 'list_page'))
        
    return dict(form=form)

@auth.requires_signature()
def delete():
    logger.info("The delete button was clicked")
    record = db(db.product.id == request.args(0)).select().first()
    if record:
        record.delete_record()

    redirect(URL('default', 'list_page'))






