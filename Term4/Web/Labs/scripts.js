window.onload = () => { 
  let feedbackModal = document.getElementById("feedbackModal");
  let openFeedbackButton = document.getElementById("openModalButton");
  let closeFeedbackButton = document.getElementById("closeFeedbackButton");


  openFeedbackButton.onclick = () => {
    feedbackModal.style.display = "block";
    feedbackModal.style.animationName = "show";
  }


  closeFeedbackButton.onclick = () => {
    feedbackModal.style.display = "none";
  }


  window.onclick = (e) => {
    if (e.target == feedbackModal) {
      feedbackModal.style.display = "none";
    }
  }


  let catalog = document.getElementById("catalog");
  let deliveryAndPayment = document.getElementById("deliveryAndPayment");
  let contacts = document.getElementById("contacts");

  let catalogFooter = document.getElementById("catalogFooter");
  let deliveryAndPaymentFooter = document.getElementById("deliveryAndPaymentFooter");
  let contactsFooter = document.getElementById("contactsFooter");


  let routToCatalog = document.getElementById("routToCatalog");
  let routToDeliveryAndPayment = document.getElementById("routToDeliveryAndPayment");
  let routToContacts = document.getElementById("routToContacts");

  routToCatalog.onclick = catalogFooter.onclick = () => {
    catalog.style.display = "block";
    deliveryAndPayment.style.display = "none";
    contacts.style.display = "none";
  }

  routToDeliveryAndPayment.onclick = deliveryAndPaymentFooter.onclick = () => {
    catalog.style.display = "none";
    deliveryAndPayment.style.display = "block";
    contacts.style.display = "none";
  }

  routToContacts.onclick = contactsFooter.onclick = () => {
    catalog.style.display = "none";
    deliveryAndPayment.style.display = "none";
    contacts.style.display = "block";
  }


  let changes = document.getElementById("changes");
  let closeToast = document.getElementById("closeToast");

  closeToast.onclick = () => {
    changes.style.display = "none";
  }

};
