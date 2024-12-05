function fetchData() {
    const name = localStorage.getItem('name');
    const email = localStorage.getItem('email');
    const image = localStorage.getItem('image');

    const dataDisplay = document.getElementById('dataDisplay');
    const imageDisplay = document.getElementById('imageDisplay');

    dataDisplay.innerHTML = name && email ? `<p>Nome: ${name}</p><p>Email: ${email}</p>` : "<p>Nenhum dado encontrado.</p>";
    if (image) {
        imageDisplay.src = image;
        imageDisplay.style.display = 'block';
    } else {
        imageDisplay.style.display = 'none';
    }
}

function openFormPage() {
    window.location.href = 'post.html';
}

function openUpdatePage() {
    window.location.href = 'put.html';
}

function deleteImage() {
    localStorage.removeItem('image');
    alert('Imagem excluída com sucesso!');
    fetchData();
}

function updateEmail() {
    const newEmail = prompt("Digite o novo email:");
    if (newEmail) {
        localStorage.setItem('email', newEmail);
        alert('Email atualizado com sucesso!');
        fetchData();
    }
}
